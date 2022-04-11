// Fill out your copyright notice in the Description page of Project Settings.


#include "GlyphPlayer.h"

#include <ios>

#include "Serialization/BufferArchive.h"
#include "Glyph.h"


// Sets default values
AGlyphPlayer::AGlyphPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGlyphPlayer::BeginPlay()
{
	Super::BeginPlay();
	CurrentProcessedGlyph.Init(0, GlyphResolution * GlyphResolution);
	OnnxGlyphModel = new OnnxModel(ONNXModelFilePath, EOnnxProvider::GPU_DirectML, 0);
}

FVector AGlyphPlayer::OnControllerDrawingGlyph(FVector const Position)
{
	FVector const PointOnPlane =
        FVector::PointPlaneProject(Position , DrawPlanePoint , DrawPlaneNormal);

	FVector LocalPointOnPlane =  PointOnPlane - DrawPlanePoint;
	FVector const PlaneR = FVector::CrossProduct(DrawPlaneNormal, FVector::UpVector);
	FVector const PlaneU = FVector::CrossProduct(DrawPlaneNormal, PlaneR);

	LocalPointOnPlane = FVector(
        FVector::DotProduct(LocalPointOnPlane, PlaneR),
        FVector::DotProduct(LocalPointOnPlane, PlaneU),
        0);

	if(FVector::DistSquared(LastSamplePoint, LocalPointOnPlane) > SampleDistance * SampleDistance)
	{
		GlyphRecording.Add(LocalPointOnPlane);
	}
	
	return  PointOnPlane;
}

void AGlyphPlayer::OnGlyphFinished()
{
	ProcessGlyph();
	
	if(bShouldClassify) ClassifyGlyph();
	
	GlyphRecording.Empty();
}

void AGlyphPlayer::SaveGlyphsToFile()
{
	if(FFileHelper::SaveArrayToFile(SavedProcessedGlyphs, * (ExportFilePath + ExportFileName)))
	{
		UE_LOG(LogTemp, Log, TEXT("Successfully saved glyphs to file %s at %s"), *ExportFileName, *ExportFilePath)
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("failed saving glyphs to file %s at %s"), *ExportFileName, *ExportFilePath)
	}
}

void AGlyphPlayer::LoadGlyphsFromFile()
{
	if(FFileHelper::LoadFileToArray(SavedProcessedGlyphs, *(ExportFilePath + ExportFileName)))
	{
		UE_LOG(LogTemp, Log, TEXT("Successfully loaded glyphs from file %s at %s"), *ExportFileName, *ExportFilePath)
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("failed loading glyphs from file %s at %s"), *ExportFileName, *ExportFilePath)
	}
}


void AGlyphPlayer::SaveCurrentGlyph()
{
	SavedProcessedGlyphs.Append(CurrentProcessedGlyph);
}

void AGlyphPlayer::ProcessGlyph()
{
	float XMin = 10000000000, YMin = 100000000000;
	float XMax = -1000000000, YMax = -1000000000;

	CurrentProcessedGlyph.Init(0, GlyphResolution * GlyphResolution);
	
	for (FVector const GlyphP : GlyphRecording)
	{
		if(GlyphP.X < XMin) XMin = GlyphP.X;
		if(GlyphP.Y < YMin) YMin = GlyphP.Y;
		if(GlyphP.X > XMax) XMax = GlyphP.X;
		if(GlyphP.Y > YMax) YMax = GlyphP.Y;
	}

	XMax -= XMin;
	YMax -= YMin;

	float const XScaleFactor = static_cast<float>(GlyphResolution - 1) / XMax;
	float const YScaleFactor = static_cast<float>(GlyphResolution - 1) / YMax;
	
	for (FVector GlyphP : GlyphRecording)
	{
		GlyphP.X -= XMin;
		GlyphP.Y -= YMin;

		float scaledGlyphX = GlyphP.X * XScaleFactor;
		float scaledGlyphY = GlyphP.Y * YScaleFactor;
		
		int const Index = FMath::RoundToInt(scaledGlyphY) * 32 + FMath::RoundToInt(scaledGlyphX);

		if(Index <= CurrentProcessedGlyph.Num())
		{
			CurrentProcessedGlyph[Index] = 1;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Glyph point (%f,%f) is bigger than resolution"), scaledGlyphX, scaledGlyphY)
		}
	}
}

void AGlyphPlayer::ClassifyGlyph()
{
	TArray<int64> const InputShape = { 1, 32, 32, 1 };
	TArray<int64> const OutputShape = { 1, 10 };

	TArray<float> inputs;
	TArray<float> Outputs;

	inputs.Init(0, GlyphResolution * GlyphResolution);
	Outputs.Init(0, 10);

	FOnnxTensorInfo const InputShapeTensorInfo =
        UOnnxUtilityLibrary::constructOnnxTensorInfo("conv2d_input", InputShape, EOnnxTensorDataType::FLOAT);
	
	FOnnxTensorInfo const OutputShapeTensorInfo =
        UOnnxUtilityLibrary::constructOnnxTensorInfo("dense_1", OutputShape, EOnnxTensorDataType::FLOAT);
        
	for(int i = 0; i <  CurrentProcessedGlyph.Num(); i++)
	{
		inputs[i] = CurrentProcessedGlyph[i];
	}

	OnnxGlyphModel->bindInput(InputShapeTensorInfo, inputs.GetData());
	OnnxGlyphModel->bindOutput(OutputShapeTensorInfo, Outputs.GetData());

	OnnxGlyphModel->run();

	int BiggestIndex = 0;

	for(int i = 0; i < Outputs.Num(); i++)
	{
		if(Outputs[i] > Outputs[BiggestIndex]) BiggestIndex = i;
	}


	if(OnGlyphDrawn.IsBound())
	{
		for (int i = 0; i < Glyphs.Num(); i++)
		{
			if(Glyphs[i]->GlyphID == static_cast<GlyphEnum>(BiggestIndex))
				OnGlyphDrawn.Broadcast(Glyphs[BiggestIndex]);
		}
	}
}

// Called every frame
void AGlyphPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGlyphPlayer::SetInternalMovement(bool State)
{
	InternalMovementEnabled = State;
}

void AGlyphPlayer::MovePlayer(FVector DeltaMove)
{
	FHitResult MoveResult;
	int Iteration = 0;

	while (!DeltaMove.IsNearlyZero() && Iteration < 5)
	{
		AddActorLocalOffset(DeltaMove, true, &MoveResult);
		DeltaMove -= DeltaMove * MoveResult.Time;

		if(!MoveResult.bBlockingHit) break;

		if(MoveResult.bStartPenetrating)
		{
			AddActorLocalOffset(MoveResult.Normal * MoveResult.PenetrationDepth);
		}

		DeltaMove -= FVector::DotProduct(DeltaMove, MoveResult.Normal) * DeltaMove;
		Iteration++;
	}
}

void AGlyphPlayer::PlayerBaseMovement(float DeltaTime)
{
	if(!InternalMovementEnabled) return;

	Velocity += MovementInput * MovementSpeed * DeltaTime;
	if(!bIsGrounded)
	{
		Velocity += FVector::UpVector * GravityForce * DeltaTime;
	}
	
	MovePlayer(Velocity * DeltaTime);
}

void AGlyphPlayer::SetForwardMovementInput(float Forward)
{
	MovementInput.X = Forward;
}

void AGlyphPlayer::SetRightMovementInput(float Right)
{
	MovementInput.Y = Right;
}

void AGlyphPlayer::SetDrawPlane(FVector const DrawPlaneP, FVector const DrawPlaneN)
{
	DrawPlaneNormal = DrawPlaneN;
	DrawPlanePoint = DrawPlaneP;
}

// Called to bind functionality to input
void AGlyphPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
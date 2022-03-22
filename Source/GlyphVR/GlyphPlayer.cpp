// Fill out your copyright notice in the Description page of Project Settings.


#include "GlyphPlayer.h"

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
	
}

// Called every frame
void AGlyphPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGlyphPlayer::SetDrawPlane(UPrimitiveComponent* DrawPlane)
{
	PlaneP = DrawPlane->GetComponentLocation();
	PlaneR = DrawPlane->GetRightVector();
	PlaneU = DrawPlane->GetUpVector();
	
}

FVector AGlyphPlayer::OnControllerDrawingGlyph(FVector Position)
{
	FVector pointOnPlane =
		FVector::PointPlaneProject(PlaneP ,PlaneP + PlaneR ,PlaneP + PlaneU);

	//UE_LOG(LogTemp, Log, TEXT("(%f,%f,%f)"), pointOnPlane.X, pointOnPlane.Y, pointOnPlane.Z)
	//pointOnPlane = FVector(FVector::DotProduct())
	GlyphRecording.Add(pointOnPlane);
	return  pointOnPlane;

	
}

// Called to bind functionality to input
void AGlyphPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


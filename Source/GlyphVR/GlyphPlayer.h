// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OnnxModel.h"
#include "OnnxUtilityLibrary.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GlyphPlayer.generated.h"

UCLASS()
class GLYPHVR_API AGlyphPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGlyphPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FVector> GlyphRecording;
	void ProcessGlyph();
	void ClassifyGlyph();

	TArray<uint8> CurrentProcessedGlyph;
	TArray<uint8> SavedProcessedGlyphs;
	
	FVector DrawPlanePoint;
	FVector DrawPlaneNormal;
	FVector LastSamplePoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float SampleDistance = 1;
	
	UPROPERTY(EditDefaultsOnly)
	int GlyphResolution = 32;
	
	UPROPERTY(EditDefaultsOnly, Category="Machine Learning")
	FString ExportFilePath;
	UPROPERTY(EditDefaultsOnly, Category="Machine Learning")
	FString ExportFileName;
	
	UPROPERTY(EditDefaultsOnly, Category="Machine Learning")
	FString ONNXModelFilePath;
	
	UPROPERTY(EditDefaultsOnly, Category="Machine Learning")
	bool bShouldClassify = true;
	
	
	UFUNCTION(BlueprintCallable)
	void SetDrawPlane(FVector DrawPlaneP, FVector DrawPlaneN);
	
	UFUNCTION(BlueprintCallable)
	void OnGlyphFinished();

	
	OnnxModel* OnnxGlyphModel;

	UFUNCTION(BlueprintCallable)
	void SaveGlyphsToFile();
	UFUNCTION(BlueprintCallable)
	void LoadGlyphsFromFile();
	UFUNCTION(BlueprintCallable)
	void SaveCurrentGlyph();
	UFUNCTION(BlueprintCallable)
	FVector OnControllerDrawingGlyph(FVector Position);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "OnnxModel.h"
#include "CoreMinimal.h"

#include "GlyphDataAsset.h"
#include "GameFramework/Pawn.h"
#include "GlyphPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGlyphDrawn, UGlyphDataAsset*, GlyphDrawn);

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

	bool InternalMovementEnabled = true;
	
	TArray<uint8> CurrentProcessedGlyph;
	TArray<uint8> SavedProcessedGlyphs;
	
	FVector DrawPlanePoint;
	FVector DrawPlaneNormal;
	FVector LastSamplePoint;

	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetInternalMovement(bool state);
	UPROPERTY(EditDefaultsOnly)
	TArray<UGlyphDataAsset*> Glyphs;

	void MovePlayer(FVector DeltaMove);
	
	void PlayerBaseMovement(float DeltaTime);

	void SetForwardMovementInput(float Forward);
	void SetRightMovementInput(float Right);

	FVector MovementInput;
	FVector Velocity;
	bool bIsGrounded;

	UPROPERTY(BlueprintAssignable, Category="Glyph")
	FOnGlyphDrawn OnGlyphDrawn;

	UPROPERTY(EditDefaultsOnly, Category="Glyph")
	float SampleDistance = 1;
	
	UPROPERTY(EditDefaultsOnly, Category="Glyph")
	int GlyphResolution = 32;
	
	UPROPERTY(EditDefaultsOnly, Category="Machine Learning")
	FString ExportFilePath;
	UPROPERTY(EditDefaultsOnly, Category="Machine Learning")
	FString ExportFileName;
	
	UPROPERTY(EditDefaultsOnly, Category="Machine Learning")
	FString ONNXModelFileName;
	
	UPROPERTY(EditDefaultsOnly, Category="Machine Learning")
	bool bShouldClassify = true;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float GravityForce = -980;
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float MovementSpeed = 300;
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

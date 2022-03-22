// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<FVector> GlyphRecording;
	FVector PlaneP;
	FVector PlaneR;
	FVector PlaneU;
	void SetDrawPlane(UPrimitiveComponent* DrawPlane);

	UFUNCTION(BlueprintCallable)
	FVector OnControllerDrawingGlyph(FVector Position);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

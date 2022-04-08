// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "LevitateSelfSpell.generated.h"

/**
 * 
 */
UCLASS()
class GLYPHVR_API ALevitateSelfSpell : public ASpell
{
	GENERATED_BODY()

	float LevitationTimer = 0;
	FVector ControllerStartPos;

	void MovePlayer(float DeltaTime);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void InitSpell(FSpellInput Input) override;
	UPROPERTY(EditAnywhere)
	float Sensitivity = 1;
	UPROPERTY(EditAnywhere)
	float MaxSpeed = 1000;
	UPROPERTY(EditAnywhere)
	float Duration = 10;

	AGlyphPlayer* Player;
	USceneComponent* Controller;
};
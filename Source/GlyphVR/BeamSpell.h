// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "BeamSpell.generated.h"

/**
 * 
 */
UCLASS()
class GLYPHVR_API ABeamSpell : public ASpell
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	TArray<GlyphEnum> ElementGlyphs;
	USceneComponent* CastingController;

	
};

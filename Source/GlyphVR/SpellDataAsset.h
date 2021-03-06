// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Glyph.h"
#include "Spell.h"
#include "SpellDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class GLYPHVR_API USpellDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASpell> Spell;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<GlyphEnum> SpellRecipe;
};

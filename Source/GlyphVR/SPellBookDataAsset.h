// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Glyph.h"
#include "Spell.h"
#include "SpellDataAsset.h"
#include "SPellBookDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class GLYPHVR_API USPellBookDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TSubclassOf<ASpell> GetSpell(TArray<GlyphEnum> Glyphs);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USpellDataAsset*> Spells;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USpellDataAsset*> ComplexSpells;


};

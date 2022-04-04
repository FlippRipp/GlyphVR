// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Glyph.h"
#include "GlyphCombinationTable.generated.h"


/**
 * 
 */
UCLASS()
class GLYPHVR_API UGlyphCombinationTable : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	TMap<TPair<GlyphEnum, GlyphEnum>, GlyphCombosEnum> GlyphCombos;
};

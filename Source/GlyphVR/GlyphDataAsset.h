// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GlyphDataAsset.generated.h"

UCLASS()
class GLYPHVR_API UGlyphDataAsset : public UDataAsset
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString GlyphName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int GlyphID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* GlyphActor;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Glyph.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

USTRUCT(BlueprintType)
struct FSimpleSpellInput
{
	GENERATED_BODY()

	USceneComponent* MainHandController;
	USceneComponent* OffHandController;
	USceneComponent* Head;

	TArray<GlyphEnum> ElementGlyphs;
};

UCLASS()
class GLYPHVR_API ASpell : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ASpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool HasInitialized = false;
	UFUNCTION(BlueprintCallable)
	virtual void InitSpell(FSimpleSpellInput Input);
};

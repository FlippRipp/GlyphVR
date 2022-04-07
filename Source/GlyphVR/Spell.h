// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Glyph.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInit, const TArray<GlyphEnum>&, Elements);

USTRUCT(BlueprintType)
struct FSimpleSpellInput
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	USceneComponent* MainHandController;
	UPROPERTY(BlueprintReadWrite)
	USceneComponent* OffHandController;
	UPROPERTY(BlueprintReadWrite)
	USceneComponent* Head;
	UPROPERTY(BlueprintReadWrite)
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

	float GetElementsDamageModifier(TArray<GlyphEnum> DamageTypes);

	bool HasInitialized = false;
	UFUNCTION(BlueprintCallable)
	virtual void InitSpell(FSimpleSpellInput Input);

	UPROPERTY(BlueprintAssignable)
	FOnInit OnInit;

	virtual void Damage(AActor* Target, float BaseDamage, TArray<GlyphEnum> DamageTypes);
};

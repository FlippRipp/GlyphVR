// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Glyph.h"
#include "GlyphPlayer.h"
#include "SpellEffect.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInit, const TArray<GlyphEnum>&, Elements);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnImpact, FVector, ImpactPoint, FVector, ImpactDirection,
	const TArray<GlyphEnum>&, Elements, const TArray<TSubclassOf<ASpellEffect>>&, VFX, AActor*, Target);

USTRUCT(BlueprintType)
struct FSpellInput
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	AGlyphPlayer* Player;
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
	virtual void InitSpell(FSpellInput Input);

	UPROPERTY(BlueprintAssignable)
	FOnInit OnInit;
	UPROPERTY(EditAnywhere)
	TMap<GlyphEnum, TSubclassOf<ASpellEffect>> SpellEffectMap;

	UPROPERTY(BlueprintAssignable)
	FOnImpact OnImpact;

	virtual void Damage(AActor* Target, float BaseDamage, TArray<GlyphEnum> DamageTypes);
};

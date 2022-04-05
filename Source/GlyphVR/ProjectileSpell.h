// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "ProjectileSpell.generated.h"

/**
 * 
 */
UCLASS()
class GLYPHVR_API AProjectileSpell : public ASpell
{
	GENERATED_BODY()

public:
	TArray<GlyphEnum> ElementGlyphs;
	USceneComponent* CastingController;
	
	
	virtual void Tick(float DeltaTime) override;
	virtual void InitSpell(FSimpleSpellInput Input) override;
	UPROPERTY(EditAnywhere)
	float Speed = 1000;
	
};

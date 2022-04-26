// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpell.h"

void AProjectileSpell ::Tick(float DeltaTime) 
{
	if(!HasInitialized) return;
	Super::Tick(DeltaTime);
	FVector VelocityDelta = CastingController->GetRightVector() * Speed * DeltaTime;
	FHitResult MoveResult;
	AddActorLocalOffset(VelocityDelta, true, &MoveResult);

	if(MoveResult.bBlockingHit)
	{
		TArray<TSubclassOf<ASpellEffect>> SpellEffects;
		
		for(GlyphEnum Glyph : ElementGlyphs)
		{
			TSubclassOf<ASpellEffect> SpellEffect = *SpellEffectMap.Find(Glyph);
			
			if(SpellEffect != nullptr)
			{
				SpellEffects.Add(SpellEffect);
			}
		}
		
		FVector ImpactDirection = (MoveResult.ImpactPoint - GetActorLocation()).GetSafeNormal(); 
		OnImpact.Broadcast(MoveResult.ImpactPoint, ImpactDirection, ElementGlyphs, SpellEffects, MoveResult.Actor.Get());
		Damage(MoveResult.Actor.Get(), 100, ElementGlyphs);
	}
}

void AProjectileSpell::InitSpell(FSpellInput Input)
{
	Super::InitSpell(Input);
	if(Input.MainHandController != nullptr)
	{
		CastingController = Input.MainHandController;	
	}

	if(Input.ElementGlyphs.Num() > 0)
	{
		ElementGlyphs = Input.ElementGlyphs;
	}
	
	HasInitialized = true;
}
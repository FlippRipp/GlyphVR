// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpell.h"

void AProjectileSpell ::Tick(float DeltaTime) 
{
	if(!HasInitialized) return;
	Super::Tick(DeltaTime);
	FVector VelocityDelta = CastingController->GetForwardVector() * Speed * DeltaTime;
	FHitResult MoveResult;
	AddActorLocalOffset(VelocityDelta, true, &MoveResult);

	if(MoveResult.bBlockingHit)
	{
		const TArray<TSubclassOf<ASpellEffect>> SpellEffects = GetSpellEffects(ElementGlyphs);
		const FVector ImpactDirection = (MoveResult.ImpactPoint - GetActorLocation()).GetSafeNormal(); 
		OnImpact.Broadcast(MoveResult.ImpactPoint, ImpactDirection, ElementGlyphs, SpellEffects, MoveResult.Actor.Get());

		FString ActorName = MoveResult.Actor->GetName();
		UE_LOG(LogTemp, Log, TEXT("%s"), *ActorName)
		Damage(MoveResult.Actor.Get(), 100, ElementGlyphs);
		Destroy();
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
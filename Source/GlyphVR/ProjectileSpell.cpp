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
		  
	}
}

void AProjectileSpell::InitSpell(FSimpleSpellInput Input)
{
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
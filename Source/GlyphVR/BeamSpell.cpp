// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamSpell.h"

void ABeamSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!HasInitialized) return;

	if(BeamTimer > BeamDuration) Destroy();

	BeamTimer += DeltaTime;

	FHitResult TraceResults;
	FVector TraceStart = CastingController->GetComponentLocation();
	FVector TraceEnd = TraceStart + CastingController->GetForwardVector() * MaxRange;
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	QueryParams.AddIgnoredActor(CastingController->GetOwner());
	
	GetWorld()->LineTraceSingleByChannel(TraceResults, TraceStart, TraceEnd, TraceChannel, QueryParams);
	if(TraceResults.bBlockingHit)
	{
		FVector ImpactDirection = (TraceResults.ImpactPoint - TraceStart).GetSafeNormal();
		
		OnImpact.Broadcast(TraceResults.ImpactPoint, ImpactDirection,
			ElementGlyphs, GetSpellEffects(ElementGlyphs), TraceResults.Actor.Get());
		Damage(TraceResults.Actor.Get(), BeamDamage * DeltaTime, ElementGlyphs);
	}
}

void ABeamSpell::InitSpell(FSpellInput Input)
{
	Super::InitSpell(Input);
	CastingController = Input.MainHandController;
	ElementGlyphs = Input.ElementGlyphs;
}
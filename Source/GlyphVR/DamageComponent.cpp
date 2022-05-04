// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UDamageComponent::Damage(float Damage, TArray<GlyphEnum> DamageTypes, FVector ImpactPoint)
{
	HitPoints = FMath::Max(HitPoints - Damage, 0.f);
	if(OnDamage.IsBound()) OnDamage.Broadcast(Damage, DamageTypes, ImpactPoint);
	if(HitPoints == 0)
	{
		GetOwner()->Destroy();
	}
}

void UDamageComponent::SetIsBurning(bool State)
{
	IsBurning = State;
	IsBurningTimer = 0;
	if(State)
	{
		SetIsDoused(false);
		IsBurningTimer = BurnTime / 2;
	}
	OnIsBurningChanged.Broadcast(State);
}

void UDamageComponent::SetIsDoused(bool State)
{
	IsDoused = State;
	IsDousedTimer = 0;
	if(State)
	{
		SetIsBurning(false);
	}
	OnIsDousedChanged.Broadcast(State);
}

void UDamageComponent::StatusEffectUpdate(float DeltaTime)
{
	if(IsBurning)
	{
		IsBurningTimer += DeltaTime;
		HitPoints -= BurnDamage * DeltaTime;
		if(BurnTime < IsBurningTimer)
		{
			SetIsBurning(false);
		}
	}
	if(IsDoused)
	{
		IsDousedTimer += DeltaTime;
		if(IsDousedTimer > DousedTime)
		{
			SetIsDoused(false);
		}
	}
}

// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	StatusEffectUpdate(DeltaTime);
	// ...
}


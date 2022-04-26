// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"

#include "DamageComponent.h"

// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ASpell::GetElementsDamageModifier(TArray<GlyphEnum> DamageTypes)
{
	return 1;
}

void ASpell::InitSpell(FSpellInput Input)
{
	OnInit.Broadcast(Input.ElementGlyphs);
	HasInitialized = true;
}

void ASpell::Damage(AActor* Target, float BaseDamage, TArray<GlyphEnum> DamageTypes)
{
	UDamageComponent* TargetDamageComponent;
	float TotalDamage = BaseDamage;
	TargetDamageComponent = Cast<UDamageComponent>(Target->GetComponentByClass(TSubclassOf<UDamageComponent>()));
	if(TargetDamageComponent)
	{
		for(GlyphEnum DamageType : DamageTypes)
		{
			switch (DamageType)
			{
			case GlyphEnum::Air:
				TotalDamage *= 0.5;
				break;
			case  GlyphEnum::Fire:
				TotalDamage *= 2;
				TargetDamageComponent->SetIsBurning(true);
				break;
			case GlyphEnum::Earth:
				TotalDamage *= 1.2;
				break;
			case GlyphEnum::Water:
				TotalDamage *= 0.8;
				TargetDamageComponent->SetIsDoused(true);
				break;
			}
		}
		TargetDamageComponent->Damage(BaseDamage, DamageTypes, GetActorLocation());
	}
}


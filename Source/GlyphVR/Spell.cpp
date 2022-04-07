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
	
}

void ASpell::InitSpell(FSimpleSpellInput Input)
{
	OnInit.Broadcast(Input.ElementGlyphs);
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
			//TODO Add damage Modifies total damage
			TotalDamage *= 1;
		}
		
		TargetDamageComponent->Damage(BaseDamage, DamageTypes, GetActorLocation());
	}
}


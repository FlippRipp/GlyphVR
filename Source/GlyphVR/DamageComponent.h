// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Glyph.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDamage,float, Damage, const TArray<GlyphEnum>&, DamageTypes, FVector, ImpactPoint);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GLYPHVR_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent();

	virtual void Damage(float Damage, TArray<GlyphEnum> DamageTypes, FVector ImpactPoint);

	UPROPERTY(BlueprintAssignable)
	FOnDamage OnDamage;

	UPROPERTY(EditAnywhere)
	float HitPoints = 100;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Glyph.generated.h"

UENUM(Blueprintable)
enum class GlyphEnum : uint8
{
	SpellCircle UMETA(DisplayName = "SpellCircle"),		//0
	//Element glyphs
	Air UMETA(DisplayName = "Air"),					//Myr 1
	Fire UMETA(DisplayName = "Fire"),				//Sif 2
	Earth UMETA(DisplayName = "Earth"),				//Lod 3
	Water UMETA(DisplayName = "Water"),				//Nar 4
	Light UMETA(DisplayName = "Light"),				//Fax 5
	Dark UMETA(DisplayName = "Dark"),				//Nyx 6
	//Shape glyphs
	Beam UMETA(DisplayName = "Beam"),				//ark 7
	Projectile UMETA(DisplayName = "Projectile"),	//Mol 8
	Buff UMETA(DisplayName = "Buff"),				//kas 9
	Shield UMETA(DisplayName = "Shield"),			//Bir 10

	Default UMETA(DisplayName = "Default")			//Bir 10
};

UENUM(Blueprintable)
enum class GlyphCombosEnum : uint8
{
    //Element glyph Combos
    Frost UMETA(DisplayName = "Frost"),	 //air & dark

};

UCLASS()
class GLYPHVR_API AGlyph : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlyph();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

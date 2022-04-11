// Fill out your copyright notice in the Description page of Project Settings.


#include "LevitateSelfSpell.h"

void ALevitateSelfSpell::MovePlayer(float DeltaTime)
{
	FVector ControllerDifference = Controller->GetRelativeLocation() - ControllerStartPos; 
	FVector DeltaMove = (ControllerDifference * Sensitivity).GetClampedToSize(0, MaxSpeed) * DeltaTime;
	Player->MovePlayer(DeltaMove);
}

void ALevitateSelfSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(!HasInitialized) return;
	
	LevitationTimer += DeltaTime;
	MovePlayer(DeltaTime);
	
	if(LevitationTimer > Duration)
	{
		Player->SetInternalMovement(true);
		Destroy();
	}
}

void ALevitateSelfSpell::InitSpell(FSpellInput Input)
{
	Super::InitSpell(Input);
	Player = Input.Player;
	Controller = Input.MainHandController;
	if(Player != nullptr)
		Player->SetInternalMovement(false);
	LevitationTimer = 0;
	ControllerStartPos = Controller->GetRelativeLocation();
}

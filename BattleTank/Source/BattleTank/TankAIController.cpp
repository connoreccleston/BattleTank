// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(PlayerTank && GetPawn()))
	{
		auto aimComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();

		MoveToActor(PlayerTank, Radius);

		aimComp->AimAt(PlayerTank->GetTargetLocation());

		if (aimComp->GetAimState() == EAimState::LOCKED)
			aimComp->Fire();
	}
}

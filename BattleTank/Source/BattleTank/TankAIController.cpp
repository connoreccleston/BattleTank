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
		MoveToActor(PlayerTank, Radius);

		GetPawn()->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetTargetLocation());

		GetPawn()->FindComponentByClass<UTankAimingComponent>()->Fire();
	}
}

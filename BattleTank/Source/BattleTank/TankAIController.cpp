// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("AI controlling tank: %s"), *GetControlledTank()->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("AI found player tank: %s"), *GetPlayerTank()->GetName());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//move towards player a bit
	AimTowardsPlayer();
	//fire if ready
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::AimTowardsPlayer() const
{
	if (GetControlledTank() && GetPlayerTank())
		GetControlledTank()->AimAt(GetPlayerTank()->GetTargetLocation());
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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

		aimComp->AimAt(PlayerTank->GetActorLocation() + FVector(0, 0, 150));

		if (aimComp->GetAimState() == EAimState::LOCKED)
			aimComp->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);

		if (ensure(PossessedTank))
		{
			PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
		}
	}
}

void ATankAIController::OnTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
}

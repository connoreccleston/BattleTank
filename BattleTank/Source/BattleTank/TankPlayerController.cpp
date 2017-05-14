// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimComp = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimComp))
		FoundAimingComponent(AimComp);
	else
		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at begin play."))
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) { return; }

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
	{
		GetControlledTank()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Get screen size
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	// Get location of crosshair
	FVector2D screenLocation(viewportSizeX * CrosshairLocationX, viewportSizeY * CrosshairLocationY);

	// Get look direction
	FVector camLocation, lookDirection;
	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, camLocation, lookDirection))
	{
		// Get location of point being looked at if it is visible
		if (GetLookVectorHitLocation(lookDirection, OutHitLocation))
		{
			return true;
		}
	}

	// Otherwise location was invalid (sky)
	OutHitLocation = FVector(0.0f);
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult outHit;
	bool linetraceSuccess = false;
	linetraceSuccess = GetWorld()->LineTraceSingleByChannel
	(
		outHit,
		PlayerCameraManager->GetCameraLocation(), // start
		PlayerCameraManager->GetCameraLocation() + LookDirection * LinetraceRange, // end
		ECollisionChannel::ECC_Visibility
	);

	if (linetraceSuccess)
	{
		OutHitLocation = outHit.Location;
		return true;
	}

	return false;
}

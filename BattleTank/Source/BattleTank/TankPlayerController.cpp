// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Player controlling tank: %s"), *GetControlledTank()->GetName());
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
	if (!GetControlledTank()) { return; }

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

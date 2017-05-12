// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.3333f;

	UPROPERTY(EditAnywhere)
	float LinetraceRange = 1000000.0f; //cm = 10 Km
};

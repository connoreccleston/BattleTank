// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float Radius = 10000;

private:
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();
};

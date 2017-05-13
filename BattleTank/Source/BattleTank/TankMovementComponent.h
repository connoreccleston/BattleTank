// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void MoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Rotate(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Init(UTankTrack* LeftToSet, UTankTrack* RightToSet);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
};

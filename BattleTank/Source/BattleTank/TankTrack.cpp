// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s %f"), *GetName(), Throttle);

	//clamp throttle value

	auto AppliedForce = GetForwardVector() * Throttle * MaxDrivingForce;
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(AppliedForce, GetComponentLocation());
}



// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::MoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// prevent double speed
}

void UTankMovementComponent::Rotate(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	// prevent double speed
}

void UTankMovementComponent::Init(UTankTrack* LeftToSet, UTankTrack* RightToSet)
{
	LeftTrack = LeftToSet;
	RightTrack = RightToSet;
}

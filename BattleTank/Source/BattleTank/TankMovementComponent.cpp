// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::MoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// prevent double speed
}

void UTankMovementComponent::Rotate(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	// prevent double speed
}

void UTankMovementComponent::Init(UTankTrack* LeftToSet, UTankTrack* RightToSet)
{
	LeftTrack = LeftToSet;
	RightTrack = RightToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector ForwardIntention = MoveVelocity.GetSafeNormal();

	float speed = FVector::DotProduct(TankForward, ForwardIntention);
	float angle = FVector::CrossProduct(ForwardIntention, TankForward).Z;

	MoveForward(speed);
	Rotate(angle);

	//UE_LOG(LogTemp, Warning, TEXT("%f"), angle);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("I'm hit"));
	DriveTrack();
	ApplyCorrectingForce();
	CurrentThrottle = 0.0f;
}

// Called every frame
//void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//}

void UTankTrack::ApplyCorrectingForce()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	float sidewaysSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	FVector correctionAcc = (-sidewaysSpeed / DeltaTime) * GetRightVector();

	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = tankRoot->GetMass() * correctionAcc / 2;

	//tankRoot->AddForce(correctionForce); //what if applied at the center of the track?
	AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp(CurrentThrottle + Throttle, -1.0f, 1.0f);
}

void UTankTrack::DriveTrack()
{
	auto AppliedForce = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	AppliedForce = FVector(AppliedForce.X, AppliedForce.Y, 0.0f); // negates Z component, prevents tanks driving up cliffs, but there's probably a better way to do this
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(AppliedForce, GetComponentLocation());
}

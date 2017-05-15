// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Init(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	AmmoCount = MaxAmmo;
	LastFireTime = GetWorld()->GetTimeSeconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (currentAimState != EAimState::OOA)
	{	
		if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeSeconds)
		{
			currentAimState = EAimState::RELOADING;
		}
		else if (IsBarrelMoving())
		{
			currentAimState = EAimState::AIMING;
		}
		else
		{
			currentAimState = EAimState::LOCKED;
		}
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !(Barrel->GetForwardVector().Equals(localAimDirection, 0.01f));
	//TODO This actually gives a better aim than the algorithm used in MoveBarrelTowards
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool foundSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false
	);
	
	if (foundSolution)
	{
		localAimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(localAimDirection);
	}
}

EAimState UTankAimingComponent::GetAimState() const
{
	return currentAimState;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator CurrentBarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator CurrentTurretRotation = Turret->GetForwardVector().Rotation();
	
	FRotator DesiredRotation = AimDirection.Rotation();

	FRotator DeltaBarrel = DesiredRotation - CurrentBarrelRotation;
	FRotator DeltaTurret = DesiredRotation - CurrentTurretRotation;

	Barrel->Elevate(DeltaBarrel.Pitch);

	if (DeltaTurret.Yaw > 180.0f || DeltaTurret.Yaw < -180.0f)
		Turret->Turn(DeltaTurret.Yaw * -1.0f);
	else
		Turret->Turn(DeltaTurret.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	if (currentAimState != EAimState::RELOADING && currentAimState != EAimState::OOA)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		AmmoCount--;
		if (AmmoCount <= 0)
			currentAimState = EAimState::OOA;
	}
}

uint8 UTankAimingComponent::GetAmmoCount() 
{
	return AmmoCount;
}

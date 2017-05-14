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
	PrimaryComponentTick.bCanEverTick = false;

	// ...
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

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
		false//true
	);
	
	if (foundSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);

		//UE_LOG(LogTemp, Warning, TEXT("Aim solution found"));
	}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Aim solution NOT found"));
	//}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator CurrentBarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator CurrentTurretRotation = Turret->GetForwardVector().Rotation();
	
	FRotator DesiredRotation = AimDirection.Rotation();

	FRotator DeltaBarrel = DesiredRotation - CurrentBarrelRotation;
	FRotator DeltaTurret = DesiredRotation - CurrentTurretRotation;

	Barrel->Elevate(DeltaBarrel.Pitch);
	Turret->Turn(DeltaTurret.Yaw);
}

//void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
//{
//	Barrel = BarrelToSet;
//}
//
//void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
//{
//	Turret = TurretToSet;
//}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) >= ReloadTimeSeconds;
	if (isReloaded)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	Barrel = FindComponentByClass<UTankBarrel>();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//void ATank::AimAt(FVector HitLocation)
//{
//	//if (ensure(TankAimingComponent))
//	//	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
//}

//void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
//{
//	//TankAimingComponent->SetBarrelReference(BarrelToSet);
//	Barrel = BarrelToSet;
//}

//void ATank::SetTurretReference(UTankTurret* TurretToSet)
//{
//	TankAimingComponent->SetTurretReference(TurretToSet);
//}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) >= ReloadTimeSeconds;
	if (isReloaded)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

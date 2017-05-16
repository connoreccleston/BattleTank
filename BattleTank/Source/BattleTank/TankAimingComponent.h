// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EAimState : uint8
{
	RELOADING, AIMING, LOCKED, OOA
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Init(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = State)
	EAimState currentAimState = EAimState::AIMING;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	EAimState GetAimState() const;

	bool IsBarrelMoving();

	void AimAt(FVector HitLocation);

	void MoveBarrelTowards(FVector AimDirection);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Firing)
	uint8 GetAmmoCount();

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 5000;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadTimeSeconds = 3;

	float LastFireTime = 0;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Firing)
	uint8 MaxAmmo = 50;

	uint8 AmmoCount = 0;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector localAimDirection;

};

// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	uint8 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);

	if (DamagePoints > CurrentHealth)
		DamagePoints = CurrentHealth;

	CurrentHealth -= DamagePoints;

	UE_LOG(LogTemp, Warning, TEXT("current health %d damage amount %d"), CurrentHealth, DamagePoints);

	return (float)DamagePoints;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

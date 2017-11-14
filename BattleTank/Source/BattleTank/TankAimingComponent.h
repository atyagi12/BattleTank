// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading
};

class UTankBarrel;		// Forward Declaration
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:
	UPROPERTY(BlueprintReadOnly)
		EFiringState FiringState = EFiringState::Locked;

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 1000000;				// 1000 m/s

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	
};

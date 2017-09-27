// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"



ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlTank = GetControlledTank();

	if (!ControlTank) {
		UE_LOG(LogTemp, Warning, TEXT("No Tank possessed"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Possessing %s"), *ControlTank->GetName());
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) return;

	// Get world location of line trace from crosshair
	// If landscape hit, rotate barrel to point to location
}

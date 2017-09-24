// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlTank = GetControlledTank();

	if (!ControlTank) {
		UE_LOG(LogTemp, Warning, TEXT("No Tank possessed"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Possessing AI Tank %s"), *ControlTank->GetName());
	}

}


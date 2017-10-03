// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"

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

	UE_LOG(LogTemp, Warning, TEXT("Player controller is %s"), *(GetPlayerTank()->GetName()));

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		// TODO Move towards the player

		// Aim towards the player

		// Fire if ready

		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}

	
}

ATank * ATankAIController::GetPlayerTank() const
{

	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


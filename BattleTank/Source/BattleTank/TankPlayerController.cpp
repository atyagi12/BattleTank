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

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		// UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	}

	

	// Get world location of line trace from crosshair
	// If landscape hit, rotate barrel to point to location
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{

	// Get current position
	// Raycast forward
	// Check if any terrain or objects hit
	// Update HitLocation if hit and return true

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrossHairYLocation);

	FVector WorldDirection;

	if (GetLookDirection(ScreenLocation, WorldDirection))
	{
		FHitResult HitResult;
		if (GetLookVectorHitLocation(HitLocation, WorldDirection))
		{
			UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		}
		

	}


	
	HitLocation = FVector(1.0);
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & WorldDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		WorldDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & HitLocation, FVector WorldDirection) const
{

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + WorldDirection*LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

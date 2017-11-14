// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) {
		return;
	}
	FoundAimingComponent(AimingComponent);

	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) {
		return;
	}

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}

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

	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(HitLocation, LookDirection);
	}

	return false;
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

bool ATankPlayerController::GetLookVectorHitLocation(FVector & HitLocation, FVector LookDirection) const
{

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection*LineTraceRange;

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

#include "TankPlayerController.h"

 #include "TankAimingComponent.h"

#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* ControlledTank = Cast<ATank>(InPawn);

		if (ControlledTank)
		{
			ControlledTank->TankDeathDelegate.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
		}
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(AimingComponent))
	{
		return;
	}

	FVector HitLocation(0);

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find crosshair position in pixel coordinates

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// Map the screen position of the crosshair to world direction

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along look direction and check what was hit
		return GetLookDirectionHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D &ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;	
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookDirectionHitLocation(const FVector& LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Camera))
	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}

void ATankPlayerController::OnPossessedTankDeath()
{
	// Activate spectator mode after tank possessed by player destroyed
	StartSpectatingOnly();
}

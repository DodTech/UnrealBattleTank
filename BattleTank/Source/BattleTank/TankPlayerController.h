#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Get tank possessed by this controller
	ATank* GetControlledTank() const;

	// Move the tank barrel towards aiming point specified by crosshair
	// (shot would hit where crosshair intersects the world)
	void AimTowardsCrosshair();

	// Get location where linetrace hits landscape through crosshair
	// Returns true if hit landscape and false otherwise
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	// Get direction based on deprojecting screen coordinates at world
	bool GetLookDirection(const FVector2D &ScreenLocation, FVector& LookDirection) const;

	// Get location that was hit by line-tracing along look direction
	bool GetLookDirectionHitLocation(const FVector& LookDirection, FVector& HitLocation) const;

private:

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.35f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 100000.0f;
};

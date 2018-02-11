#pragma once

#include "CoreMinimal.h"

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

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

	bool GetLookDirection(const FVector2D &ScreenLocation, FVector& LookDirection) const;

	bool GetLookDirectionHitLocation(const FVector& LookDirection, FVector& HitLocation) const;

private:

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.35f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 100000.0f;
};

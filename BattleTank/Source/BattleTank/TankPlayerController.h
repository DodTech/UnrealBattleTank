#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/*!
 * \class ATankPlayerController
 *
 * \brief Class representing player controller.
 *
 * \author Ivan Tustanivskyi
 * \date February 2018
 */
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

protected:
	// Event which indicates that tank has attached aiming component
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponentReference);

private:
	// Move the tank barrel towards aiming point specified by crosshair
	// (shot would hit where crosshair intersects the landscape)
	void AimTowardsCrosshair();

	// Get location where linetrace hits landscape through crosshair
	// Returns true if hit landscape and false otherwise
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	// Get direction based on deprojecting screen coordinates at world
	bool GetLookDirection(const FVector2D &ScreenLocation, FVector& LookDirection) const;

	// Get location that was hit by line-tracing along look direction
	bool GetLookDirectionHitLocation(const FVector& LookDirection, FVector& HitLocation) const;

private:

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.35f;

	// Range in which tank can recognize objects to aim at
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 100000.0f;

private:
	// Tank aiming component
	UTankAimingComponent* AimingComponent = nullptr;
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Enumeration representing firing state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,	// tank is reloading
	Aiming,		// tank is reloaded and its barrel moving towards aiming point
	Locked,		// tank is reloaded and aiming point is captured by its barrel
	Empty		// tank has no ammo to continue shooting
};

/*!
 * \class UTankAimingComponent
 *
 * \brief Class representing tank aiming component.
 * Aiming component is responsible for tank combat behavior.
 *
 * \author Ivan Tustanivskyi
 * \date February 2018
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Initialise tank barrel and turret references
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Aim at specified location
	void AimAt(FVector HitLocation);

	// Get current tank firing status
	EFiringStatus GetFiringStatus() const;

	// Make a shot in direction that is currently pointed by tank barrel
	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Function called every frame on this ActorComponent
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// Determine how much ammo left for tank to shoot
	UFUNCTION(BlueprintCallable)
	int32 GetAmmoLeft() const;

private:
	// Move tank barrel to aim at specified direction
	void MoveBarrel(FVector AimDirection);

public:
	// Current tank firing status
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	// Amount of tank ammo (how many times tank can shoot)
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 Ammo = 20;

protected:
	// Reference to blueprint that inherits from projectile class
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Projectile launch speed
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000.0f;

	// Time that is required for tank to reload before firing
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

private:
	// Tank barrel
	UTankBarrel* Barrel = nullptr;
	// Tank turret
	UTankTurret* Turret = nullptr;
	
	// Time when last tank shot was performed
	double LastFireTime = 0.0;

	// Tolerance for comparing aiming direction and actual barrel direction vectors
	float AimingTolerance = 0.01f;

	// Flag that indicates if barrel is still moving to be aligned towards aiming direction
	bool IsBarrelMoving = false;
};
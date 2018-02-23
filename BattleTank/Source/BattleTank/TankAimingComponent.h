#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

// Enumeration representing aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,	
	Locked
};

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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Move barrel to aim at specified direction
	void MoveBarrel(FVector AimDirection);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringStatus = EFiringState::Locked;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000.0f;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};

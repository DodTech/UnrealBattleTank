#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/*!
 * \class UTankBarrel
 *
 * \brief Class representing tank barrel.
 * Barrel is attached to tank turret.
 * It can be moved up and down with given speed for aiming purposes.
 * Barrel movement is limited because of tank structure.
 * At the end of barrel there is a socket which is used as spawn point for projectiles.
 *
 * \author Ivan Tustanivskyi
 * \date February 2018
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Elevate barrel with given speed
	// -1 is max downward speed and +1 is max upward speed
	void Elevate(float RelativeSpeed);
	
private:
	// Maximum possible elevation change for barrel per second
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 10.0f;

	// Maximum possible elevation for barrel
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 40.0f;

	// Minimum possible elevation for barrel
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = 0.0f;
};
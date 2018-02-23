#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/*!
 * \class UTankTurret
 *
 * \brief Class representing tank turret. 
 * Turret is attached to tank body. Also turret is coupled with tank barrel.
 * It can be rotated left and right with given speed for aiming purposes.
 * When turret rotates attached tank barrel moves with it as well.
 *
 * \author Ivan Tustanivskyi
 * \date February 2018
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Rotate turret with specified speed
	// -1 is max leftward speed and +1 is max rightward speed
	void Rotate(float RelativeSpeed);
	
private:
	// Maximum possible rotation for turret per second
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 15.0f;
};

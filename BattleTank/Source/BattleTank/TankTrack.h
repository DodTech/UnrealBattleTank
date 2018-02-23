#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/*!
 * \class UTankTrack
 *
 * \brief Class representing tank track.
 * Tank has left and right tracks which are attached to its body.
 * Track is responsible for making tank move.
 *
 * \author Ivan Tustanivskyi
 * \date February 2018
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Apply force to move tank
	// Movement speed and direction depends on throttle value
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
private:
	// Maximum force that track can apply to tank when throttle (in Newtons)
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.0f;
};

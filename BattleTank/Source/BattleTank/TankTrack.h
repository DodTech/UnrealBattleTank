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
	// Sets default values for this component properties
	UTankTrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Function called every frame on this ActorComponent
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// Apply force for tank slippage compensation
	void ApplySidewayForce();

public:	
	// Set track throttle value that defines movement speed and direction
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// Apply force to track to move tank	
	void DriveTrack();

private:
	// Handle hit event to perform necessary movement operations
	// It is called only when tank track stays on the ground (hits the landscape)
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
private:
	// Maximum force that track can apply to tank when throttle (in Newtons)
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.0f;

	// Current throttle value
	float CurrentThrottle = 0.0f;
};

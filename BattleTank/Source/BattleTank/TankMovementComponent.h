#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/*!
 * \class UTankMovementComponent
 *
 * \brief Class representing tank movement component.
 * Movement component is responsible tank movement initiated both by user or AI.
 *
 * \author Ivan Tustanivskyi
 * \date February 2018
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	// Initialise tank tracks references
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	// Move tank forward/backward with given throw
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);
	// Move tank aside with given throw
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveAside(float Throw);

private:
	// Handle part of pathfinding logic called by AI controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	// Tank left track
	UTankTrack* LeftTrack = nullptr;
	// Tank right track
	UTankTrack* RightTrack = nullptr;	
};
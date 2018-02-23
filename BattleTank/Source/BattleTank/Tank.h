#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

/*!
 * \class ATank
 *
 * \brief Class representing tank.
 * 
 * Tank can be controlled both by player or AI.
 * Tank consists of body, left and right tracks, turret and barrel.
 * It also includes aiming and movement components that encapsulate tank behavior.
 * From this class corresponding blueprint (Tank_BP) is derived.
 *
 * \author Ivan Tustanivskyi
 * \date February 2018
 */
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
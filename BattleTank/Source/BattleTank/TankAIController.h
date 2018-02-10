#pragma once

#include "CoreMinimal.h"

#include "Tank.h"

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ATank* GetControlledTank() const;	
};

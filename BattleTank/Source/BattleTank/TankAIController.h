#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Get tank possessed by this controller
	ATank* GetControlledTank() const;	

	// Get tank possessed by player controller
	ATank* GetPlayerTank() const;
};

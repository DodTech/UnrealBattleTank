#pragma once

#include "CoreMinimal.h"

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Get tank possessed by this controller
	ATank* GetControlledTank() const;
};

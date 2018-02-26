#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/*!
 * \class ATankAIController
 *
 * \brief Class representing AI controller.
 * AI controller is responsible for managing enemy tanks.
 *
 * \author Ivan Tustanivskyi
 * \date February 2018
 */
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

protected:
	// Distance between AI and player tanks that should be reached to make AI controlled tank stop moving towards player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000.0f;

private:
	// Tank aiming component
	UTankAimingComponent* AimingComponent = nullptr;
};

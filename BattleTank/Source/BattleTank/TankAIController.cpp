#include "TankAIController.h"

#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get tank possessed by this controller
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	// Get tank possessed by player controller
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ControlledTank || !PlayerTank)
	{
		return;
	}

	// TODO Move towards the player

	// Aim towards the player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	// Fire at player when ready
	ControlledTank->Fire();
}

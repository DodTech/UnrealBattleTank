#include "TankAIController.h"

#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get tank possessed by this controller
	auto ControlledTank = GetPawn();

	// Get tank possessed by player controller
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ControlledTank || !PlayerTank)
	{
		return;
	}

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);	

	// Aim towards the player

	if (!ensure(AimingComponent))
	{
		return;
	}

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire at player when ready
	AimingComponent->Fire();
}

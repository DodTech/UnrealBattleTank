#include "TankAIController.h"

#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetControlledTank() || !GetPlayerTank())
	{
		return;
	}

	// TODO Move towards the player

	// Aim towards the player
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

	// TODO Fire if ready
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

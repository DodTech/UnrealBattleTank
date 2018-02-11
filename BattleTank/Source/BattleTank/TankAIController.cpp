#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled AI tank: %s"), *ControlledTank->GetName())

		auto PlayerTank = GetPlayerTank();

		if (PlayerTank)
		{
			UE_LOG(LogTemp, Warning, TEXT("This AI tank aiming at %s"), *PlayerTank->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("There is no controlled AI tank!"))
	}
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

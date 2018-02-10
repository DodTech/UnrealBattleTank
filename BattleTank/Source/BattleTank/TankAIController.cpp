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

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

#include "TankAIController.h"

#include "TankAimingComponent.h"

#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* ControlledTank = Cast<ATank>(InPawn);

		if (ControlledTank)
		{
			ControlledTank->TankDeathDelegate.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
		}
	}
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

	// Fire at player when ready (locked)
	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("ATankAIController OnPossessedTankDeath"));
}

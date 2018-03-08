#include "Tank.h"

#include "UnrealMathUtility.h"

ATank::ATank()
{
 	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("%s is hit"), *GetName());

	// Determine how much damage to apply  
	int32 DamageToApply = FMath::Clamp<float>(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth);

	// Decrease tank current health
	CurrentHealth -= DamageToApply;

	// Check if tank is still "alive"
	if (CurrentHealth <= 0)
	{
		TankDeathDelegate.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return static_cast<float>(CurrentHealth) / static_cast<float>(StartingHealth);
}

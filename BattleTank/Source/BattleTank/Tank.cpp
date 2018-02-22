#include "Tank.h"

#include "TankBarrel.h"
#include "TankTurret.h"

#include "TankAimingComponent.h"

#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent))
	{
		return;
	}

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	
	// Spawn projectile at the end of the barrel if tank is already reloaded

	if (IsReloaded)
	{
		if (!ensure(Barrel))
		{
			return;
		}

		FVector ProjectileSpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator ProjectileSpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileSpawnLocation, ProjectileSpawnRotation);

		if (Projectile)
		{
			Projectile->LaunchProjectile(LaunchSpeed);

			LastFireTime = FPlatformTime::Seconds();
		}
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}


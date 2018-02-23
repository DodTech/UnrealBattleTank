#include "TankAimingComponent.h"

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel))
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	ESuggestProjVelocityTraceOption::Type TraceOption = ESuggestProjVelocityTraceOption::DoNotTrace;

	// Calculate the out launch velocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, TraceOption))
	{
		// Obtain aiming direction for barrel
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::Fire()
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

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...	
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}

	// Calculate difference between current barrel rotation and aiming direction
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}


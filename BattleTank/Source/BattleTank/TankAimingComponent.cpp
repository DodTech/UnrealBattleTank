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
	PrimaryComponentTick.bCanEverTick = true;
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

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel))
	{
		return;
	}

	if (!ensure(ProjectileBlueprint))
	{
		return;
	}

	if (FiringStatus != EFiringStatus::Reloading)
	{
		FVector ProjectileSpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator ProjectileSpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));

		// Spawn projectile at the end of the barrel
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileSpawnLocation, ProjectileSpawnRotation);

		if (Projectile)
		{
			Projectile->LaunchProjectile(LaunchSpeed);
			
			LastFireTime = FPlatformTime::Seconds();
		}
	}
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// Ensure that tank will perform initial reload right after game start
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Determine if there was enough time for tank to reload since last shot was done (or game started)
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!IsReloaded)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving)
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
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

	if (Barrel->GetForwardVector().Equals(AimDirection, AimingTolerance))
	{
		IsBarrelMoving = false;
		return;
	}

	IsBarrelMoving = true;

	Barrel->Elevate(DeltaRotator.Pitch);

	// Determine optimal rotation direction to ensure that turret uses shortest trajectory while aiming
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{		
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}	
}

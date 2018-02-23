#include "Projectile.h"

AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));

	if (ProjectileMovementComponent)
	{
		// Prevent projectile from activation at the moment it is spawned, since it should be activated explicitly
		ProjectileMovementComponent->bAutoActivate = false;
	}
}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();	
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
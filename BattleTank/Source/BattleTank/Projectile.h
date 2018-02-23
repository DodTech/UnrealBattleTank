#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

/*!
 * \class AProjectile
 *
 * \brief Class representing tank projectile.
 * Projectiles are instantiated by tank aiming component on firing event.
 * After launch projectile starts moving in direction pointed by tank barrel with given speed.
 * Projectile is destroyed when it meets an obstacle (landscape or enemy tank).
 * From this class corresponding blueprint (Projectile_BP) is derived.
 *
 * \author Ivan Tustanivskyi
 * \date February 2018
 */
UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Launch projectile with specified speed
	void LaunchProjectile(float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Projectile sub-object for movement
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;	
};
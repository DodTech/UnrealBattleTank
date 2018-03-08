#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
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

private:
	// Handle hit event to simulate explosion when projectile reaches its target
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	// Handle timer event to destroy projectile after hitting target
	UFUNCTION()
	void OnTimer();

private:
	// Mesh representing projectile body
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

	// Effect that presented right after projectile is launched 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr;

	// Effect that presented when projectile hits the target
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ImpactBlast = nullptr;

	// Impulse created be projectile when it hits target
	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ExplosionForce = nullptr;

	// Delay time for projectile destruction after hitting target
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 10.0f;

	// Amount of damage that projectile deals to enemy
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Damage = 20.0f;

private:
	// Projectile sub-object for movement
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;	
};
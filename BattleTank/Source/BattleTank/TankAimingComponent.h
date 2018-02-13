#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Aim at specified location
	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	// TODO Add SetTurretReference

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

private:
	// Move barrel to aim at specified direction
	void MoveBarrel(FVector AimDirection);

private:
	UStaticMeshComponent* Barrel = nullptr;
};

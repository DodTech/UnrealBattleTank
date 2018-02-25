#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Calculate slippage speed
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out required acceleration this frame to correct
	FVector CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());

	// Get reference to tank body
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	
	// Calculate correction sideway force ( F = m * a)
	FVector CorrectionForce = CorrectionAcceleration * TankRoot->GetMass() / 2;

	// Apply sideway force for slippage correction
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	// Calculate force that should be applied to move tank
	// Throttle sign also determines movement direction (negative for backward and positive for forward)
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;

	// Get location at which force should be applied
	// It is determined by socket which is used to attach track to tank body
	FVector ForceLoaction = GetComponentLocation();

	// Get reference to tank body
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	// Apply force to tank body to make it move
	TankRoot->AddForceAtLocation(ForceApplied, ForceLoaction);
}
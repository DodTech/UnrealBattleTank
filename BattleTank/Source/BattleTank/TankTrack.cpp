#include "TankTrack.h"

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
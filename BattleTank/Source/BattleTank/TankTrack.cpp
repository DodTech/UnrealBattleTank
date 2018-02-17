#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s is throttling %f"), *GetName(), Throttle);

	// TODO Clamp Throttle value
}

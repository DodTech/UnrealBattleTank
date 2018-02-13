#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	UE_LOG(LogTemp, Warning, TEXT("%s elevates barrel with %f dps"), *GetOwner()->GetName(), DegreesPerSecond);

	// Apply new elevation to barrel object
}

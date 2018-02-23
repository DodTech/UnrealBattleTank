#include "TankBarrel.h"

#include "UnrealMathUtility.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Normalize barrel elevation speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	// Calculate new elevation value for barrel
	float ElevationRange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationRange;

	// Ensure that barrel elevation value doesn't exceed specified limits
	float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	// Apply new elevation to barrel object
	SetRelativeRotation(FRotator(Elevation, 0.0f, 0.0f));
}

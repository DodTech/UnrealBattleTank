#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	// Calculate new rotation value for turret
	float RotationRange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = RelativeRotation.Yaw + RotationRange;

	// Apply new rotation to turret object
	SetRelativeRotation(FRotator(0.0f, Rotation, 0.0f));
}

#include "AccelerationSystem.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void AccelerationSystem::Update(Scene& scene, std::vector<Acceleration>& accelerations, float deltaTime)
{
	int requiredComponentsMask = 1 << static_cast<int>(Velocity::ID);

	for (auto& acceleration : accelerations)
	{
		if ((scene.GetComponentMask(acceleration.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		// find delta velocity
		Vector2 deltaInternalVelocity = Vector2Scale(acceleration.internalAcceleration, deltaTime);
		Vector2 deltaExternalVelocity = Vector2Scale(acceleration.externalAcceleration, deltaTime);

		// add to velocity
		Velocity& velocity = scene.GetComponent<Velocity>(acceleration.entity);
		velocity.internalVelocity = Vector2Add(velocity.internalVelocity, deltaInternalVelocity);
		velocity.externalVelocity = Vector2Add(velocity.externalVelocity, deltaExternalVelocity);
	}
}

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
		Vector2 deltaVelocity = Vector2Scale(acceleration.acceleration, deltaTime);

		// add to velocity
		Velocity& velocity = scene.GetComponent<Velocity>(acceleration.entity);
		velocity.velocity = Vector2Add(velocity.velocity, deltaVelocity);
	}
}

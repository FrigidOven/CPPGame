#include "AccelerationSystem.h"
#include "Scene.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void AccelerationSystem::Update(Scene* scene, std::vector<Acceleration>& accelerations)
{
	for (auto& acceleration : accelerations)
	{
		int componentMask = scene->GetComponentMask(acceleration.entity);
		int requiredComponentsMask = 1 << Velocity::ID;
		if ((componentMask & requiredComponentsMask) != requiredComponentsMask)
			continue;

		float deltaTime = GetFrameTime();

		// find delta velocity
		Vector2 deltaVelocity = Vector2Scale(acceleration.acceleration, deltaTime);

		// add to velocity
		Velocity& velocity = scene->GetComponent<Velocity>(acceleration.entity);
		velocity.velocity = Vector2Add(velocity.velocity, deltaVelocity);
	}
}

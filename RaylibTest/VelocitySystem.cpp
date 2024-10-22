#include "VelocitySystem.h"
#include "Scene.h"

#include <raymath.h>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void VelocitySystem::Update(Scene* scene, std::vector<Velocity>& velocities)
{
	for (auto& velocity  : velocities)
	{
		int componentMask = scene->GetComponentMask(velocity.entity);
		int requiredComponentsMask = 1 << Spatial::ID;
		if ((componentMask & requiredComponentsMask) != requiredComponentsMask)
			continue;

		float deltaTime = GetFrameTime();

		// find displacement
		Vector2 displacement = Vector2Scale(velocity.velocity, deltaTime);

		if (scene->HasComponent<VelocityBasedMovement>(velocity.entity))
			displacement = Vector2Add(displacement, Vector2Scale(scene->GetComponent<VelocityBasedMovement>(velocity.entity).velocity, deltaTime));

		if (scene->HasComponent<VelocityBasedSpeedLimiter>(velocity.entity))
		{
			float maxVelocity= scene->GetComponent<VelocityBasedSpeedLimiter>(velocity.entity).maxVelocity;
			displacement = Vector2ClampValue(displacement, 0.0f, maxVelocity * deltaTime);
			velocity.velocity = Vector2ClampValue(velocity.velocity, 0.0f, maxVelocity);
		}

		// add to position
		Spatial& spatial = scene->GetComponent<Spatial>(velocity.entity);
		spatial.position = Vector2Add(spatial.position, displacement);
	}
}
#include "VelocitySystem.h"
#include "Scene.h"

#include <raymath.h>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void VelocitySystem::Update(Scene& scene, std::vector<Velocity>& velocities, float deltaTime)
{
	int requiredComponentsMask = 1 << Spatial::ID;

	for (auto& velocity  : velocities)
	{
		if ((scene.GetComponentMask(velocity.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		// find displacement
		Vector2 displacement = Vector2Scale(velocity.velocity, deltaTime);
		// add velocity based movement
		if (scene.HasComponent<Movement>(velocity.entity))
		{
			Movement& movement = scene.GetComponent<Movement>(velocity.entity);
			if (movement.mode == MovementMode::VelocityBased)
				displacement = Vector2Add(displacement, Vector2Scale(movement.direction, deltaTime));
		}
		// limit speed if applicable
		if (scene.HasComponent<SpeedLimiter>(velocity.entity))
		{
			float maxVelocity= scene.GetComponent<SpeedLimiter>(velocity.entity).maxVelocity;
			displacement = Vector2ClampValue(displacement, 0.0f, maxVelocity * deltaTime);
			velocity.velocity = Vector2ClampValue(velocity.velocity, 0.0f, maxVelocity);
		}
		// add to position
		Spatial& spatial = scene.GetComponent<Spatial>(velocity.entity);
		spatial.position = Vector2Add(spatial.position, displacement);
	}
}
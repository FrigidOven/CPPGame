#include "MovementSystem.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void MovementSystem::Update(Scene& scene, std::vector<Movement>& movements)
{
	for (auto& movement : movements)
	{
		if((movement.mode == MovementMode::ForceBased) && scene.HasComponent<Rigidbody>(movement.entity))
		{
			Vector2& pushingForce = scene.GetComponent<Rigidbody>(movement.entity).internalPushingForce;
			pushingForce = Vector2Add(pushingForce, movement.direction);
		}
		else if((movement.mode == MovementMode::VelocityBased) && scene.HasComponent<Velocity>(movement.entity))
		{
			Vector2& velocity = scene.GetComponent<Velocity>(movement.entity).internalVelocity;
			velocity = movement.direction;
		}
	}
}
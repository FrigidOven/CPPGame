#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void MovementSystem::Update(Scene* scene, std::vector<Movement>& movementComponents)
{
	for (auto& movement : movementComponents)
	{
		if (movement.isForceBased)
			scene->GetComponent<Force>(movement.entity).internalForce = movement.direction;
		else
			scene->GetComponent<RigidBody>(movement.entity).velocity = movement.direction;
	}
}
#include "MovementSystem.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void MovementSystem::Update(Scene& scene, std::vector<Movement>& movements)
{
	// only movements with MovementMode::ForceBased will be handeled here.
	// VelocityBased movements must be handleded further down the chain in the velocity system.
	int requiredComponentsMask = (1 << Movement::ID) | (1 << ForceReceiver::ID);

	for (auto& movement : movements)
	{
		if ((scene.GetComponentMask(movement.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		if((movement.mode == MovementMode::ForceBased))
		{
			Vector2& pushingForce = scene.GetComponent<ForceReceiver>(movement.entity).pushingForce;
			pushingForce = Vector2Add(pushingForce, movement.direction);
		}
	}
}
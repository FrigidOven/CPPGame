#include "VelocityBasedMovementControllerSystem.h"
#include "Scene.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void VelocityBasedMovementControllerSystem::Update(Scene& scene, std::vector<VelocityBasedMovementController>& velocityBasedMovementControllers)
{
	int requiredComponentsMask = 1 << Direction::ID;

	for (auto& velocityBasedMovementController : velocityBasedMovementControllers)
	{
		if ((scene.GetComponentMask(velocityBasedMovementController.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		scene.RemoveComponent<VelocityBasedMovement >(velocityBasedMovementController.entity);
		Direction& direction = scene.GetComponent<Direction>(velocityBasedMovementController.entity);

		if (velocityBasedMovementController.up.isActive)
		{
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(0.0f, -velocityBasedMovementController.speed));
			direction.direction = Orientation::Up;
		}
		else if (velocityBasedMovementController.left.isActive)
		{
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(-velocityBasedMovementController.speed, 0.0f));
			direction.direction = Orientation::Left;
		}
		else if (velocityBasedMovementController.down.isActive)
		{
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(0.0f, velocityBasedMovementController.speed));
			direction.direction = Orientation::Down;
		}
		else if (velocityBasedMovementController.right.isActive)
		{
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(velocityBasedMovementController.speed, 0.0f));
			direction.direction = Orientation::Right;
		}
	}
}
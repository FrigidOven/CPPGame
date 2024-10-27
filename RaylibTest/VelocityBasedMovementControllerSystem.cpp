#include "VelocityBasedMovementControllerSystem.h"
#include "Scene.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void VelocityBasedMovementControllerSystem::Update(Scene& scene, std::vector<VelocityBasedMovementController>& velocityBasedMovementControllers)
{
	for (auto& velocityBasedMovementController : velocityBasedMovementControllers)
	{
		scene.RemoveComponent<VelocityBasedMovement >(velocityBasedMovementController.entity);

		if (velocityBasedMovementController.up.isActive)
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(0.0f, -velocityBasedMovementController.speed));

		else if (velocityBasedMovementController.left.isActive)
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(-velocityBasedMovementController.speed, 0.0f));

		else if (velocityBasedMovementController.down.isActive)
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(0.0f, velocityBasedMovementController.speed));

		else if (velocityBasedMovementController.right.isActive)
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(velocityBasedMovementController.speed, 0.0f));
	}
}
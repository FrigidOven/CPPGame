#include "ForceBasedMovementControllerSystem.h"
#include "Scene.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ForceBasedMovementControllerSystem::Update(Scene* scene, std::vector<ForceBasedMovementController>& forceBasedMovementControllers)
{
	for (auto& forceBasedMovementController : forceBasedMovementControllers)
	{
		int componentMask = scene->GetComponentMask(forceBasedMovementController.entity);

		scene->RemoveComponent<ForceBasedMovement>(forceBasedMovementController.entity);

		if (forceBasedMovementController.up.isActive)
			scene->AddComponent<ForceBasedMovement>(forceBasedMovementController.entity, Vector2(0.0f, -forceBasedMovementController.force));

		else if (forceBasedMovementController.left.isActive)
			scene->AddComponent<ForceBasedMovement>(forceBasedMovementController.entity, Vector2(-forceBasedMovementController.force, 0.0f));

		else if (forceBasedMovementController.down.isActive)
			scene->AddComponent<ForceBasedMovement>(forceBasedMovementController.entity, Vector2(0.0f, forceBasedMovementController.force));

		else if (forceBasedMovementController.right.isActive)
			scene->AddComponent<ForceBasedMovement>(forceBasedMovementController.entity, Vector2(forceBasedMovementController.force, 0.0f));
	}
}
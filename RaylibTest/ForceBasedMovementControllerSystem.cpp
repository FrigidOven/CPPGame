#include "ForceBasedMovementControllerSystem.h"
#include "Scene.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ForceBasedMovementControllerSystem::Update(Scene* scene, std::vector<ForceBasedMovementController>& forceBasedMovementControllers)
{
	int requiredComponentsMask = 1 << Velocity::ID;

	for (auto& forceBasedMovementController : forceBasedMovementControllers)
	{
		if ((scene->GetComponentMask(forceBasedMovementController.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		float stoppingForceMagnitude = 0.0f;
		bool hadMovement = scene->HasComponent<ForceBasedMovement>(forceBasedMovementController.entity);

		if (hadMovement)
			stoppingForceMagnitude = Vector2Length(scene->GetComponent<ForceBasedMovement>(forceBasedMovementController.entity).force);

		scene->RemoveComponent<ForceBasedMovement>(forceBasedMovementController.entity);

		if (forceBasedMovementController.up.isActive)
			scene->AddComponent<ForceBasedMovement>(forceBasedMovementController.entity, Vector2(0.0f, -forceBasedMovementController.force));
		else if (forceBasedMovementController.left.isActive)
			scene->AddComponent<ForceBasedMovement>(forceBasedMovementController.entity, Vector2(-forceBasedMovementController.force, 0.0f));
		else if (forceBasedMovementController.down.isActive)
			scene->AddComponent<ForceBasedMovement>(forceBasedMovementController.entity, Vector2(0.0f, forceBasedMovementController.force));
		else if (forceBasedMovementController.right.isActive)
			scene->AddComponent<ForceBasedMovement>(forceBasedMovementController.entity, Vector2(forceBasedMovementController.force, 0.0f));
		else if (hadMovement)
		{
			Vector2 velocity = scene->GetComponent<Velocity>(forceBasedMovementController.entity).velocity;

			if (scene->HasComponent<Friction>(forceBasedMovementController.entity))
				stoppingForceMagnitude *= scene->GetComponent<Friction>(forceBasedMovementController.entity).coefficient;

			scene->AddComponent<StoppingForce>(forceBasedMovementController.entity, Vector2Scale(Vector2Normalize(velocity), -1.0f * stoppingForceMagnitude));
		}
	}
}
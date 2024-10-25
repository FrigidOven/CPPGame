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

		int entity = forceBasedMovementController.entity;

		Vector2 upForce(0.0f, -forceBasedMovementController.force);
		Vector2 leftForce(-forceBasedMovementController.force, 0.0f);
		Vector2 downForce(0.0f, forceBasedMovementController.force);
		Vector2 rightForce(forceBasedMovementController.force, 0.0f);

		Vector2 previousForce(0.0f, 0.0f);
		float frictionCoefficient = 0.0f;

		bool wasMoving = scene->HasComponent<ForceBasedMovement>(entity);

		if (wasMoving)
			previousForce = scene->GetComponent<ForceBasedMovement>(entity).force;

		if (wasMoving && scene->HasComponent<Friction>(entity))
			frictionCoefficient = scene->GetComponent<Friction>(entity).coefficient;

		bool wasMoving[4] =
		{
			Vector2Equals(previousForce, upForce),
			Vector2Equals(previousForce, leftForce),
			Vector2Equals(previousForce, downForce),
			Vector2Equals(previousForce, rightForce)
		};
		bool isMoving[4] =
		{
			forceBasedMovementController.up.isActive,
			forceBasedMovementController.left.isActive,
			forceBasedMovementController.down.isActive,
			forceBasedMovementController.right.isActive
		};

		for (int i = 0; i < 4; i++)
		{
			if (wasMoving[i] && !isMoving[i])
				scene->RemoveComponent<ForceBasedMovement>(entity);



		}


	}












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
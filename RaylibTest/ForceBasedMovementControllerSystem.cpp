#include "ForceBasedMovementControllerSystem.h"
#include "Scene.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ForceBasedMovementControllerSystem::Update(Scene& scene, std::vector<ForceBasedMovementController>& forceBasedMovementControllers)
{
	for (auto& forceBasedMovementController : forceBasedMovementControllers)
	{
		int entity = forceBasedMovementController.entity;

		Vector2 currentForce(0.0f, 0.0f);
		Vector2 currentStoppingForce(0.0f, 0.f);
		float frictionCoefficient = 0.0f;

		bool hasMovement = scene.HasComponent<ForceBasedMovement>(entity);

		if (hasMovement)
			currentForce = scene.GetComponent<ForceBasedMovement>(entity).force;
		if (hasMovement && scene.HasComponent<Friction>(entity))
			frictionCoefficient = scene.GetComponent<Friction>(entity).coefficient;
		if (scene.HasComponent<StoppingForce>(entity))
			currentStoppingForce = scene.GetComponent<StoppingForce>(entity).force;

		// all arrays ordered: up, left, down, right
		Vector2 directions[4] =
		{
			Vector2(0.0f, -forceBasedMovementController.force),
			Vector2(-forceBasedMovementController.force, 0.0f),
			Vector2(0.0f, forceBasedMovementController.force),
			Vector2(forceBasedMovementController.force, 0.0f)
		};
		bool isMoving[4] =
		{
			Vector2Equals(currentForce, directions[0]),
			Vector2Equals(currentForce, directions[1]),
			Vector2Equals(currentForce, directions[2]),
			Vector2Equals(currentForce, directions[3])
		};
		bool wantsToMove[4] =
		{
			forceBasedMovementController.up.isActive,
			forceBasedMovementController.left.isActive,
			forceBasedMovementController.down.isActive,
			forceBasedMovementController.right.isActive
		};

		// doesn't want to move and is moving
		if (!wantsToMove[0] && !wantsToMove[1] && !wantsToMove[2] && !wantsToMove[3] && 
			(isMoving[0] || isMoving[1] || isMoving[2] || isMoving[3]))
		{
			scene.RemoveComponent<ForceBasedMovement>(entity);
			scene.RemoveComponent<StoppingForce>(entity);
			scene.AddComponent<StoppingForce>(entity, Vector2Add(currentStoppingForce, Vector2Scale(currentForce, -frictionCoefficient)));
			continue;
		}

		// wants to move somewhere else and is moving
		for (int i = 0; i < 4; i++)
		{
			if (wantsToMove[i] && !isMoving[i])
			{
				scene.RemoveComponent<ForceBasedMovement>(entity);
				scene.RemoveComponent<StoppingForce>(entity);

				scene.AddComponent<StoppingForce>(entity, Vector2Add(currentStoppingForce, Vector2Scale(currentForce, -frictionCoefficient)));
				scene.AddComponent<ForceBasedMovement>(entity, directions[i]);
			}
		}
	}
}
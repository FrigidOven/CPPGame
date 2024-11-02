#include "MovementSystem.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void MovementSystem::Update(Scene& scene, std::vector<MovementController>& movementControllers)
{
	for (auto& movementController : movementControllers)
	{
		if (movementController.mode == MovementMode::ForceBased)
			CreateForceBasedMovement(scene, movementController);
		else
			CreateVelocityBasedMovement(scene, movementController);
	}
}
/*
===================================================================================================
 Private Functions
===================================================================================================
*/
void MovementSystem::CreateForceBasedMovement(Scene& scene, MovementController& movementController)
{
	int entity = movementController.entity;
	Tag& tags = scene.GetComponent<Tag>(entity);

	Direction requestedDirection = movementController.requestedDirection;

	bool hadMovement = scene.HasComponent<Movement>(entity);
	bool hadStopingForce = scene.HasComponent<StoppingForce>(entity);
	bool hasFriction = scene.HasComponent<Friction>(entity);

	// If already moving in the requested direction or is not moving and does not want to
	if ((hadMovement && tags.direction == requestedDirection) || 
		 (!hadMovement && requestedDirection == Direction::None))
		return;

	Vector2 currentForce = hadMovement ? scene.GetComponent<Movement>(entity).direction : Vector2Zero();
	Vector2 newForce = Vector2Scale(DirectionToVector2(requestedDirection), movementController.magnitude);

	float frictionCoefficient = hasFriction ? scene.GetComponent<Friction>(entity).coefficient : 0.0f;

	Vector2 currentStoppingForce = hadStopingForce ? scene.GetComponent<StoppingForce>(entity).force : Vector2Zero();
	Vector2 newStoppingForce = Vector2Scale(currentForce, -frictionCoefficient);

	newStoppingForce.x = currentForce.x * newForce.x <= 0.0f ? newStoppingForce.x : 0.0f;
	newStoppingForce.y = currentForce.y * newForce.y <= 0.0f ? newStoppingForce.y : 0.0f;

	scene.RemoveComponent<Movement>(entity);
	scene.RemoveComponent<StoppingForce>(entity);

	// Was not moving and wants to move
	if (!hadMovement && requestedDirection != Direction::None)
	{
		tags.direction = requestedDirection;
		tags.state = State::Moving;
		scene.AddComponent<Movement>(entity, MovementMode::ForceBased, newForce);
	}
	// Was moving but wants to change direction
	else if (hadMovement && requestedDirection != Direction::None)
	{
		tags.direction = requestedDirection;
		scene.AddComponent<Movement>(entity, MovementMode::ForceBased, newForce);
		scene.AddComponent<StoppingForce>(entity, Vector2Add(currentStoppingForce, newStoppingForce));
	}
	// Was moving but wants to stop
	else if (hadMovement && requestedDirection == Direction::None)
	{
		tags.state = State::Idle;
		scene.AddComponent<StoppingForce>(entity, Vector2Add(currentStoppingForce, newStoppingForce));
	}
}
void MovementSystem::CreateVelocityBasedMovement(Scene& scene, MovementController& movementController)
{
	int entity = movementController.entity;
	Tag& tags = scene.GetComponent<Tag>(entity);

	Vector2 newMovementVelocity = Vector2Scale(DirectionToVector2(movementController.requestedDirection), movementController.magnitude);

	scene.RemoveComponent<Movement>(entity);

	if (movementController.requestedDirection != Direction::None)
	{
		tags.state = State::Moving;
		tags.direction = movementController.requestedDirection;
		scene.AddComponent<Movement>(entity, MovementMode::VelocityBased, newMovementVelocity);
	}
	else
		tags.state = State::Idle;
}
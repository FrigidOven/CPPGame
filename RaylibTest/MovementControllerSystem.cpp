#include "MovementControllerSystem.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void MovementControllerSystem::Update(Scene& scene, std::vector<MovementController>& movementControllers)
{
	int requiredComponentsMask = (1 << Velocity::ID);

	for (auto& movementController : movementControllers)
	{
		if ((scene.GetComponentMask(movementController.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		if (movementController.mode == MovementMode::ForceBased)
			HandleForceBasedMovement(scene, movementController);
		else
			HandleVelocityBasedMovement(scene, movementController);
	}
}
/*
===================================================================================================
 Private Functions
===================================================================================================
*/
void MovementControllerSystem::HandleForceBasedMovement(Scene& scene, MovementController& movementController)
{
	int entity = movementController.entity;
	Tag& tags = scene.GetComponent<Tag>(entity);

	Direction requestedDirection = movementController.requestedDirection;
	bool hadMovement = scene.HasComponent<Movement>(entity);
	bool hadStoppingForce = scene.HasComponent<StoppingForce>(entity);

	// Was not moving and does not want to move
	// OR no change in movement direction
	if ((!hadMovement && requestedDirection == Direction::None) ||
		hadMovement && requestedDirection == tags.direction)
		return;

	float frictionCoefficient = scene.HasComponent<Friction>(entity) ? scene.GetComponent<Friction>(entity).coefficient : 0.0f;

	// Wants to stop
	if (requestedDirection == Direction::None)
	{
		tags.state = State::Idle;
		scene.RemoveComponent<Movement>(entity);

		Vector2 stoppingForce = Vector2Scale(Vector2Normalize(scene.GetComponent<Velocity>(entity).velocity), -frictionCoefficient * movementController.magnitude);
		if (hadStoppingForce)
			scene.GetComponent<StoppingForce>(entity).force = stoppingForce;
		else
			scene.AddComponent<StoppingForce>(entity, stoppingForce);
	}
	// Was moving, had stopping force, and wanted to change directions
	else if (hadMovement && hadStoppingForce && requestedDirection != tags.direction)
	{
		tags.direction = requestedDirection;
		scene.GetComponent<Movement>(entity).direction = Vector2Scale(DirectionToVector2(requestedDirection), movementController.magnitude);
		Vector2& stoppingForce = scene.GetComponent<StoppingForce>(entity).force;
		Vector2 additionalStoppingForce = Vector2Scale(scene.GetComponent<Movement>(entity).direction, -frictionCoefficient);
		additionalStoppingForce.x = DirectionToVector2(tags.direction).x * DirectionToVector2(requestedDirection).x <= 0.0f ? additionalStoppingForce.x : 0.0f;
		additionalStoppingForce.y = DirectionToVector2(tags.direction).y * DirectionToVector2(requestedDirection).y <= 0.0f ? additionalStoppingForce.y : 0.0f;
		stoppingForce = Vector2Add(stoppingForce, additionalStoppingForce);
	}
	// Was moving, did not have stopping force, and wanted to change directions
	else if (hadMovement && requestedDirection != tags.direction)
	{
		tags.direction = requestedDirection;
		scene.GetComponent<Movement>(entity).direction = Vector2Scale(DirectionToVector2(requestedDirection), movementController.magnitude);
		Vector2 stoppingForce = Vector2Scale(scene.GetComponent<Movement>(entity).direction, -frictionCoefficient);
		stoppingForce.x = DirectionToVector2(tags.direction).x * DirectionToVector2(requestedDirection).x <= 0.0f ? stoppingForce.x : 0.0f;
		stoppingForce.y = DirectionToVector2(tags.direction).y * DirectionToVector2(requestedDirection).y <= 0.0f ? stoppingForce.y : 0.0f;
		scene.AddComponent<StoppingForce>(entity, stoppingForce);
	}
	// Was not moving and wants to move
	else if (requestedDirection != Direction::None)
	{
		tags.direction = requestedDirection;
		tags.state = State::Moving;
		scene.AddComponent<Movement>(entity, MovementMode::ForceBased, Vector2Scale(DirectionToVector2(requestedDirection), movementController.magnitude));
	}
}
void MovementControllerSystem::HandleVelocityBasedMovement(Scene& scene, MovementController& movementController)
{
	int entity = movementController.entity;
	Tag& tags = scene.GetComponent<Tag>(entity);

	Direction requestedDirection = movementController.requestedDirection;
	bool hadMovement = scene.HasComponent<Movement>(entity);

	// Was not moving and does not want to move
	// OR no change in movement direction
	if ((!hadMovement && requestedDirection == Direction::None) ||
		hadMovement && requestedDirection == tags.direction)
		return;

	// Wants to stop
	if (requestedDirection == Direction::None)
	{
		tags.state = State::Idle;
		scene.RemoveComponent<Movement>(entity);
	}
	// Was moving and wanted to change directions
	else if (hadMovement && requestedDirection != tags.direction)
	{
		tags.direction = movementController.requestedDirection;
		scene.GetComponent<Movement>(entity).direction = Vector2Scale(DirectionToVector2(movementController.requestedDirection), movementController.magnitude);
	}
	//  Was not moving and wants to move
	else
	{
		tags.state = State::Moving;
		tags.direction = movementController.requestedDirection;
		scene.AddComponent<Movement>(entity, MovementMode::VelocityBased, Vector2Scale(DirectionToVector2(movementController.requestedDirection), movementController.magnitude));
	}
}
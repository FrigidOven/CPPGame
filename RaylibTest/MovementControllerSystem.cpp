#include "MovementControllerSystem.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void MovementControllerSystem::Update(Scene& scene, std::vector<MovementController>& movementControllers)
{
	for (auto& movementController : movementControllers)
	{
		int entity = movementController.entity;
		Tag& tags = scene.GetComponent<Tag>(entity);

		Direction requestedDirection = movementController.requestedDirection;
		bool hadMovement = scene.HasComponent<Movement>(entity);

		// Was not moving and does not want to move
		// OR no change in movement direction
		if ((!hadMovement && requestedDirection == Direction::None) ||
			hadMovement && requestedDirection == tags.direction)
			continue;

		// Wants to stop
		if (requestedDirection == Direction::None)
		{
			tags.state = State::Idle;
			scene.RemoveComponent<Movement>(entity);
		}
		// Was moving, had stopping force, and wanted to change directions
		else if (hadMovement && requestedDirection != tags.direction)
		{
			tags.direction = requestedDirection;
			scene.GetComponent<Movement>(entity).direction = Vector2Scale(DirectionToVector2(requestedDirection), movementController.magnitude);
		}
		// Was not moving and wants to move
		else if (requestedDirection != Direction::None)
		{
			tags.direction = requestedDirection;
			tags.state = State::Moving;
			scene.AddComponent<Movement>(entity, movementController.mode, Vector2Scale(DirectionToVector2(requestedDirection), movementController.magnitude));
		}
	}
}
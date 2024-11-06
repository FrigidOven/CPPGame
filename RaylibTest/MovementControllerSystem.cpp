#include "MovementControllerSystem.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void MovementControllerSystem::Update(Scene& scene, std::vector<MovementController>& movementControllers, float deltaTime)
{
	int requiredComponentsMask = (1 << static_cast<int>(Velocity::ID));

	for (auto& movementController : movementControllers)
	{
		if ((scene.GetComponentMask(movementController.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		int entity = movementController.entity;
		Tag& tags = scene.GetComponent<Tag>(entity);

		Direction requestedDirection = movementController.requestedDirection;
		bool hadMovement = scene.HasComponent<Movement>(entity);

		// Was not moving and does not want to move
		// OR no change in movement direction
		if ((!hadMovement && requestedDirection == Direction::None) ||
			hadMovement && requestedDirection == tags.direction)
		{
			// do nothing
		}
		// Wants to stop
		else if (requestedDirection == Direction::None)
		{
			tags.state = State::Idle;
			scene.RemoveComponent<Movement>(entity);
		}
		// Was moving, had stopping force, and wanted to change directions
		else if (hadMovement && requestedDirection != tags.direction)
		{
			tags.direction = requestedDirection;
		}
		// Was not moving and wants to move
		else if (requestedDirection != Direction::None)
		{
			tags.direction = requestedDirection;
			tags.state = State::Moving;
			scene.AddComponent<Movement>(entity, movementController.mode, Vector2Zero());
		}

		if (scene.HasComponent<Movement>(entity))
			ManageMovement(scene, movementController, scene.GetComponent<Movement>(entity), deltaTime);
	}
}
/*
===================================================================================================
 Private Functions
===================================================================================================
*/
void  MovementControllerSystem::ManageMovement(Scene& scene, MovementController& movementController, Movement& movement, float deltaTime)
{
	Vector2& velocity = scene.GetComponent<Velocity>(movement.entity).velocity;
	movement.direction = Vector2Scale(DirectionToVector2(movementController.requestedDirection), movementController.magnitude);

	switch (movement.mode)
	{
	case MovementMode::ForceBased:
		if (scene.HasComponent<Rigidbody>(movement.entity))
		{
			Rigidbody& rigidbody = scene.GetComponent<Rigidbody>(movement.entity);

			Vector2 acceleration = Vector2Scale(movement.direction, 1.0f / rigidbody.mass);
			Vector2 deceleration = Vector2Scale(rigidbody.resistingForce, 1.0f / rigidbody.mass);

			Vector2 expectedVelocity = Vector2Add(velocity, Vector2Scale(Vector2Add(acceleration, deceleration), deltaTime));

			if (Vector2Length(expectedVelocity) > movementController.topSpeed)
			{
				acceleration = Vector2ClampValue(acceleration, 0.0f, (movementController.topSpeed - Vector2Length(velocity)) / deltaTime);
				movement.direction = Vector2Scale(acceleration, rigidbody.mass);
				expectedVelocity = Vector2Add(velocity, Vector2Scale(acceleration, deltaTime));
			}
		}
		break;
	default:
		movement.direction = Vector2ClampValue(movement.direction, 0.0f, movementController.topSpeed);
		break;
	}
}
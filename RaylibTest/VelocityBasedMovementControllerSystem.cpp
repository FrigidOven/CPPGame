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
		Tag& tag = scene.GetComponent<Tag>(velocityBasedMovementController.entity);

		if (velocityBasedMovementController.up.isActive)
		{
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(0.0f, -velocityBasedMovementController.speed));
			tag.direction = Direction::Up;
			tag.state = State::Moving;
		}
		else if (velocityBasedMovementController.left.isActive)
		{
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(-velocityBasedMovementController.speed, 0.0f));
			tag.direction = Direction::Left;
			tag.state = State::Moving;
		}
		else if (velocityBasedMovementController.down.isActive)
		{
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(0.0f, velocityBasedMovementController.speed));
			tag.direction = Direction::Down;
			tag.state = State::Moving;
		}
		else if (velocityBasedMovementController.right.isActive)
		{
			scene.AddComponent<VelocityBasedMovement>(velocityBasedMovementController.entity, Vector2(velocityBasedMovementController.speed, 0.0f));
			tag.direction = Direction::Right;
			tag.state = State::Moving;
		}
		else
		{
			tag.state = State::Idle;
		}
	}
}
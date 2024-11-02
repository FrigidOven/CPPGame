#include "PlayerMovementControllerSystem.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void PlayerMovementControllerSystem::Update(Scene& scene, std::vector<Controller>& controllers)
{
	int requiredComponentsMask = (1 << MovementController::ID);

	for (auto& controller : controllers)
	{
		if ((scene.GetComponentMask(controller.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Direction requestedDirection = Direction::None;

		if (controller.up.isDown && controller.left.isDown)
			requestedDirection = Direction::UpLeft;
		else if (controller.up.isDown && controller.right.isDown)
			requestedDirection = Direction::UpRight;
		else if (controller.down.isDown && controller.left.isDown)
			requestedDirection = Direction::DownLeft;
		else if (controller.down.isDown && controller.right.isDown)
			requestedDirection = Direction::DownRight;
		else if (controller.up.isDown)
			requestedDirection = Direction::Up;
		else if (controller.left.isDown)
			requestedDirection = Direction::Left;
		else if (controller.down.isDown)
			requestedDirection = Direction::Down;
		else if (controller.right.isDown)
			requestedDirection = Direction::Right;

		scene.GetComponent<MovementController>(controller.entity).requestedDirection = requestedDirection;
	}
}
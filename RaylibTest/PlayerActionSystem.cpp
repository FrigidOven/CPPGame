#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void PlayerActionSystem::Update(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents)
{
	for (auto& playerInputListener : playerInputListenerComponents)
	{
		if (playerInputListener.up.isActive)
			scene->AddComponent<Action>(playerInputListener.entity, std::make_shared<MovementCommand>(Vector2{ 0.0f, -1000.0f }));
		else if (playerInputListener.left.isActive)
			scene->AddComponent<Action>(playerInputListener.entity, std::make_shared<MovementCommand>(Vector2{ -1000.0f, 0.0f }));
		else if (playerInputListener.down.isActive)
			scene->AddComponent<Action>(playerInputListener.entity, std::make_shared<MovementCommand>(Vector2{ 0.0f, 1000.0f }));
		else if (playerInputListener.right.isActive)
			scene->AddComponent<Action>(playerInputListener.entity, std::make_shared<MovementCommand>(Vector2{ 1000.0f, 0.0f }));
		else
		{
			Force& force = scene->GetComponent<Force>(playerInputListener.entity);
			force.internalForce = Vector2{ 0, 0 };
		}
	}
}
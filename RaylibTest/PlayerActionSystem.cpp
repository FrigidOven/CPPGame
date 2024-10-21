#include "ECS.h"

/*
===================================================================================================
 Private Functions
===================================================================================================
*/
void PlayerActionSystem::WalkUp(Scene* scene, PlayerInputListener& playerInputListener)
{
	scene->RemoveComponent<Movement>(playerInputListener.entity);
	scene->AddComponent<Movement>(playerInputListener.entity, true, Vector2{ 0.0f, -1000.0f });
}
void PlayerActionSystem::WalkLeft(Scene* scene, PlayerInputListener& playerInputListener)
{
	scene->RemoveComponent<Movement>(playerInputListener.entity);
	scene->AddComponent<Movement>(playerInputListener.entity, true, Vector2{ -1000.0f, 0.0f });
}
void PlayerActionSystem::WalkDown(Scene* scene, PlayerInputListener& playerInputListener)
{
	scene->RemoveComponent<Movement>(playerInputListener.entity);
	scene->AddComponent<Movement>(playerInputListener.entity, true, Vector2{ 0.0f, 1000.0f });
}
void PlayerActionSystem::WalkRight(Scene* scene, PlayerInputListener& playerInputListener)
{
	scene->RemoveComponent<Movement>(playerInputListener.entity);
	scene->AddComponent<Movement>(playerInputListener.entity, true, Vector2{ 1000.0f, 0.0f });
}
void PlayerActionSystem::Stop(Scene* scene, PlayerInputListener& playerInputListener)
{
	scene->RemoveComponent<Movement>(playerInputListener.entity);
}

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
			WalkUp(scene, playerInputListener);
		else if (playerInputListener.left.isActive)
			WalkLeft(scene, playerInputListener);
		else if (playerInputListener.down.isActive)
			WalkDown(scene, playerInputListener);
		else if (playerInputListener.right.isActive)
			WalkRight(scene, playerInputListener);
		else
			Stop(scene, playerInputListener);
	}
}

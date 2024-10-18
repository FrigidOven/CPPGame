#include <vector>
#include "ECS.h"
#include <raymath.h>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void PlayerActionSystem::Update(Scene* scene, std::vector<PlayerInputListener> playerInputListenerComponents)
{
	for (auto& playerInputListener : playerInputListenerComponents)
	{
		if (playerInputListener.upIsDown)
		{
			Force& force = scene->GetComponent<Force>(playerInputListener.entity);
			force.internalForce = Vector2{ 0, -10000 };
		}
		else if (playerInputListener.leftIsDown)
		{
			Force& force = scene->GetComponent<Force>(playerInputListener.entity);
			force.internalForce = Vector2{ -10000, 0 };
		}
		else if (playerInputListener.rightIsDown)
		{
			Force& force = scene->GetComponent<Force>(playerInputListener.entity);
			force.internalForce = Vector2{ 10000, 0 };
		}
		else if (playerInputListener.downIsDown)
		{
			Force& force = scene->GetComponent<Force>(playerInputListener.entity);
			force.internalForce = Vector2{ 0, 10000 };
		}
		else
		{
			Force& force = scene->GetComponent<Force>(playerInputListener.entity);
			force.internalForce = Vector2{ 0, 0 };
		}
	}
}
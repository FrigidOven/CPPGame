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
	int playerInputComponentsCount = static_cast<int>(playerInputListenerComponents.size());
	for (int i = 0; i < playerInputComponentsCount; i++)
	{
		PlayerInputListener& pil = playerInputListenerComponents[i];
		if (pil.upIsDown)
		{
			Force& force = scene->GetComponent<Force>(pil.entity);
			force.internalForce = Vector2{ 0, -30 };
		}
		else if (pil.leftIsDown)
		{
			Force& force = scene->GetComponent<Force>(pil.entity);
			force.internalForce = Vector2{ -30, 0 };
		}
		else if (pil.rightIsDown)
		{
			Force& force = scene->GetComponent<Force>(pil.entity);
			force.internalForce = Vector2{ 30, 0 };
		}
		else if (pil.downIsDown)
		{
			Force& force = scene->GetComponent<Force>(pil.entity);
			force.internalForce = Vector2{ 0, 30 };
		}
		else
		{
			Force& force = scene->GetComponent<Force>(pil.entity);
			force.internalForce = Vector2{ 0, 0 };
		}
	}
}
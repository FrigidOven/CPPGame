#include <vector>
#include "ECS.h"
#include <raymath.h>
#include <iostream>

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
		std::cout << "Acceleration is: <" << scene->GetComponent<RigidBody>(pil.entity).acceleration.x << ", " << scene->GetComponent<RigidBody>(pil.entity).acceleration.y << ">\n";
		if (pil.upIsDown)
		{
			Force& force = scene->GetComponent<Force>(pil.entity);
			force.force = Vector2Add(force.force, Vector2{ 0, -5 });
			force.force = Vector2ClampValue(force.force, 0, 5);
		}
		else if (pil.leftIsDown)
		{
			Force& force = scene->GetComponent<Force>(pil.entity);
			force.force = Vector2Add(force.force, Vector2{ -5, 0 });
			force.force = Vector2ClampValue(force.force, 0, 5);
		}
		else if (pil.rightIsDown)
		{
			Force& force = scene->GetComponent<Force>(pil.entity);
			force.force = Vector2Add(force.force, Vector2{ 5, 0 });
			force.force = Vector2ClampValue(force.force, 0, 5);
		}
		else if (pil.downIsDown)
		{
			Force& force = scene->GetComponent<Force>(pil.entity);
			force.force = Vector2Add(force.force, Vector2{ 0, 5 });
			force.force = Vector2ClampValue(force.force, 0, 5);
		}
	}
}
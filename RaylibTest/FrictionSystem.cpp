#include "GameConstants.h"
#include "FrictionSystem.h"
#include "Scene.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void FrictionSystem::Update(Scene& scene, std::vector<Friction>& frictions)
{
	const float GRAVITY = -9.8f;

	int requiredComponentsMask = (1 << ForceReceiver::ID) | (1 << Velocity::ID) | (1 << Mass::ID);

	for (auto& friction : frictions)
	{	
		if ((scene.GetComponentMask(friction.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Vector2& velocity = scene.GetComponent<Velocity>(friction.entity).velocity;
		float mass = scene.GetComponent<Mass>(friction.entity).mass;

		friction.force = Vector2Scale(Vector2Normalize(velocity), friction.coefficient * GRAVITY * mass);

		Vector2& resistingForce = scene.GetComponent<ForceReceiver>(friction.entity).resistingForce;
		resistingForce = Vector2Add(resistingForce, friction.force);
	}
}

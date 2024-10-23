#include "FrictionSystem.h"
#include "Scene.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void FrictionSystem::Update(Scene* scene, std::vector<Friction>& frictions)
{
	const float GRAVITY = -9.8f;
	//const float FRICTION_CUT_OFF_VELOCITY = 0.01f;

	for (auto& friction : frictions)
	{
		int componentMask = scene->GetComponentMask(friction.entity);
		int requiredComponentsMask = (1 << Velocity::ID) | (1 << Mass::ID);
		if ((componentMask & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Vector2& velocity = scene->GetComponent<Velocity>(friction.entity).velocity;
		float mass = scene->GetComponent<Mass>(friction.entity).mass;

		friction.force = Vector2Scale(Vector2Normalize(velocity), friction.coefficient * GRAVITY * mass);
	}
}

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
	const float GRAVITY = 9.8f;
	const float FRICTION_CUT_OFF_VELOCITY = 0.01f;

	for (auto& friction : frictions)
	{
		// initialize friction to zero
		friction.force = Vector2Zero();

		Vector2& velocity = scene->GetComponent<Velocity>(friction.entity).velocity;
		float mass = scene->GetComponent<Mass>(friction.entity).mass;

		// only find friction if velocity is above the cut off for friction
		if (Vector2Length(velocity) >= FRICTION_CUT_OFF_VELOCITY)
			friction.force = Vector2Scale(velocity, -friction.coefficient * GRAVITY * mass);
		else
			velocity = Vector2Zero();
	}
}

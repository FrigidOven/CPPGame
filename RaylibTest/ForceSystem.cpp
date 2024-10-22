#include "ForceSystem.h"
#include "Scene.h"

#include <raymath.h>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ForceSystem::Update(Scene* scene, std::vector<Force>& forces)
{
	for (auto& force : forces)
	{
		Vector2 totalForce = force.force;

		// get movement force if it exists
		if (scene->HasComponent<ForceBasedMovement>(force.entity))
			totalForce = Vector2Add(totalForce, scene->GetComponent<ForceBasedMovement>(force.entity).force);

		// get friction force if it exists
		if (scene->HasComponent<Friction>(force.entity))
			totalForce = Vector2Add(totalForce, scene->GetComponent<Friction>(force.entity).force);

		// f = ma so a = f/m
		scene->GetComponent<Acceleration>(force.entity).acceleration = Vector2Scale(totalForce, 1.0f / scene->GetComponent<Mass>(force.entity).mass);
	}
}
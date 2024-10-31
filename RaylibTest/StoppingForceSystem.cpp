#include "StoppingForceSystem.h"
#include "Scene.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void StoppingForceSystem::Update(Scene& scene, std::vector<StoppingForce>& stoppingForces)
{
	int requiredComponentsMask = 1 << Velocity::ID;

	for (size_t i = 0; i < stoppingForces.size(); i++)
	{
		if ((scene.GetComponentMask(stoppingForces[i].entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

	
		Vector2 velocity = scene.GetComponent<Velocity>(stoppingForces[i].entity).velocity;
	
		if (stoppingForces[i].force.x * velocity.x  >= 0.0f)
			stoppingForces[i].force.x = 0.0f;

		if (stoppingForces[i].force.y * velocity.y >= 0.0f)
			stoppingForces[i].force.y = 0.0f;

		if (Vector2Equals(stoppingForces[i].force, Vector2Zero()))
		{
			scene.RemoveComponent<StoppingForce>(stoppingForces[i].entity);
			i--;
		}
	}
}

#include "VelocitySystem.h"
#include "Scene.h"

#include <raymath.h>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void VelocitySystem::Update(Scene* scene, std::vector<Velocity>& velocities)
{
	for (auto& velocity  : velocities)
	{
		float deltaTime = GetFrameTime();

		// find displacement
		Vector2 displacement = Vector2Scale(velocity.velocity, deltaTime);

		// add to position
		Spatial& spatial = scene->GetComponent<Spatial>(velocity.entity);
		spatial.position = Vector2Add(spatial.position, displacement);
	}
}
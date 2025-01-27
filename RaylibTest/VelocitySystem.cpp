#include "VelocitySystem.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void VelocitySystem::Update(Scene& scene, std::vector<Velocity>& velocities, float deltaTime)
{
	int requiredComponentsMask = 1 << static_cast<int>(Spatial::ID);

	for (auto& velocity  : velocities)
	{
		if ((scene.GetComponentMask(velocity.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		// find displacement
		// scale by 100, a pixel is 1 cm, and all units are given in meters.
		Vector2 internalDisplacement = Vector2Scale(velocity.internalVelocity, 100 * deltaTime);
		Vector2 externalDisplacement = Vector2Scale(velocity.externalVelocity, 100 * deltaTime);

		// add to position
		Spatial& spatial = scene.GetComponent<Spatial>(velocity.entity);
		spatial.position = Vector2Add(spatial.position, Vector2Add(internalDisplacement, externalDisplacement));
	}
}
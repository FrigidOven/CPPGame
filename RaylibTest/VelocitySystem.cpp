#include <vector>
#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
VelocitySystem::VelocitySystem(Scene& scene, std::vector<Velocity>& velocityComponents)
	: scene(scene)
	, velocityComponents(velocityComponents)
{
}
void VelocitySystem::Update()
{
	int velocityCount = static_cast<int>(velocityComponents.size());

	for (int i = 0; i < velocityCount; i++)
	{
		float deltaTime = GetFrameTime();

		Vector2 displacement = { deltaTime * velocityComponents[i].velocity.x, deltaTime * velocityComponents[i].velocity.y };
		float angularDisplacement = deltaTime * velocityComponents[i].angularVelocity;

		Spatial& spatial = scene.GetSpatialComponent(velocityComponents[i].entity);
		
		spatial.position.x += displacement.x;
		spatial.position.y += displacement.y;

		spatial.rotation += angularDisplacement;
	}
}
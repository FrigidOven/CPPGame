#include <vector>
#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
RigidBodySystem::RigidBodySystem(Scene& scene, std::vector<RigidBody>& rigidBodyComponents)
	: scene(scene)
	, rigidBodyComponents(rigidBodyComponents)
{
}
void RigidBodySystem::Update()
{
	int rigidBodyCount = static_cast<int>(rigidBodyComponents.size());

	for (int i = 0; i < rigidBodyCount; i++)
	{
		float deltaTime = GetFrameTime();

		Vector2 displacement = { deltaTime * rigidBodyComponents[i].velocity.x, deltaTime * rigidBodyComponents[i].velocity.y };
		float angularDisplacement = deltaTime * rigidBodyComponents[i].angularVelocity;

		Spatial& spatial = scene.GetSpatialComponent(rigidBodyComponents[i].entity);
		
		spatial.position.x += displacement.x;
		spatial.position.y += displacement.y;

		spatial.rotation += angularDisplacement;

		Vector2 deltaVelocity = { deltaTime * rigidBodyComponents[i].acceleration.x, deltaTime * rigidBodyComponents[i].acceleration.y };
		float deltaAngularVelocity = deltaTime * rigidBodyComponents[i].angularAcceleration;

		rigidBodyComponents[i].velocity.x += deltaVelocity.x;
		rigidBodyComponents[i].velocity.y += deltaVelocity.y;

		rigidBodyComponents[i].angularVelocity += deltaAngularVelocity;
	}
}
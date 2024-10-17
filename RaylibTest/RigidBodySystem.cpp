#include <vector>
#include "ECS.h"
#include<raymath.h>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void RigidBodySystem::Update(Scene* scene, std::vector<RigidBody>& rigidBodyComponents)
{
	int rigidBodyCount = static_cast<int>(rigidBodyComponents.size());

	for (int i = 0; i < rigidBodyCount; i++)
	{
		float deltaTime = GetFrameTime();

		Vector2 displacement = Vector2Scale(rigidBodyComponents[i].velocity, deltaTime);
		float angularDisplacement =  rigidBodyComponents[i].angularVelocity * deltaTime;

		Spatial& spatial = scene->GetComponent<Spatial>(rigidBodyComponents[i].entity);
		
		spatial.position = Vector2Add(spatial.position, displacement);
		spatial.rotation += angularDisplacement;

		Vector2 deltaVelocity = Vector2Scale(rigidBodyComponents[i].acceleration, deltaTime);
		float deltaAngularVelocity =  rigidBodyComponents[i].angularAcceleration * deltaTime;

		rigidBodyComponents[i].velocity = Vector2Add(rigidBodyComponents[i].velocity, deltaVelocity);
		rigidBodyComponents[i].angularVelocity += deltaAngularVelocity;
	}
}
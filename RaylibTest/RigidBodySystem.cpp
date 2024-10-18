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
	for (auto& rigidBody : rigidBodyComponents)
	{
		float deltaTime = GetFrameTime();

		Vector2 displacement = Vector2Scale(rigidBody.velocity, deltaTime);
		float angularDisplacement = rigidBody.angularVelocity * deltaTime;

		Spatial& spatial = scene->GetComponent<Spatial>(rigidBody.entity);
		
		spatial.position = Vector2Add(spatial.position, displacement);
		spatial.rotation += angularDisplacement;

		Vector2 deltaVelocity = Vector2Scale(rigidBody.acceleration, deltaTime);
		float deltaAngularVelocity = rigidBody.angularAcceleration * deltaTime;

		rigidBody.velocity = Vector2Add(rigidBody.velocity, deltaVelocity);
		rigidBody.angularVelocity += deltaAngularVelocity;
	}
}
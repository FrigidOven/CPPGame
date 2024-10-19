#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "Systems.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void AccelerationSystem::Update(Scene* scene, std::vector<RigidBody>& rigidBodyComponents)
{
	for (auto& rigidBody : rigidBodyComponents)
	{
		float deltaTime = GetFrameTime();

		// find delta velocity
		Vector2 deltaVelocity = Vector2Scale(rigidBody.acceleration, deltaTime);
		float deltaAngularVelocity = rigidBody.angularAcceleration * deltaTime;

		// add to velocity
		rigidBody.velocity = Vector2Add(rigidBody.velocity, deltaVelocity);
		rigidBody.angularVelocity += deltaAngularVelocity;
	}
}

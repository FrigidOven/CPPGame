#include <vector>
#include "ECS.h"
#include <raymath.h>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void SpeedLimiterSystem::Update(Scene* scene, std::vector<SpeedLimiter>& speedLimiterComponents)
{
	for (auto& speedLimiter : speedLimiterComponents)
	{
		RigidBody& rigidBody = scene->GetComponent<RigidBody>(speedLimiter.entity);
		Vector2ClampValue(rigidBody.velocity, 0.0f, speedLimiter.maxVelocity);
		rigidBody.angularVelocity = Clamp(rigidBody.angularVelocity, -speedLimiter.maxAngularVelocity, speedLimiter.maxAngularVelocity);
	}
}
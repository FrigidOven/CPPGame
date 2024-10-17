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
	int speedLimiterCount = static_cast<int>(speedLimiterComponents.size());

	for (int i = 0; i < speedLimiterCount; i++)
	{
		RigidBody& rigidBody = scene->GetComponent<RigidBody>(speedLimiterComponents[i].entity);
		
		Vector2ClampValue(rigidBody.velocity, 0.0f, speedLimiterComponents[i].maxVelocity);
		rigidBody.angularVelocity = Clamp(rigidBody.angularVelocity, -speedLimiterComponents[i].maxAngularVelocity, speedLimiterComponents[i].maxAngularVelocity);
	}
}
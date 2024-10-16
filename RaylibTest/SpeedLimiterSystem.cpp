#include <vector>
#include "ECS.h"
#include <cmath>

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
		
		float speed = sqrtf(rigidBody.velocity.x * rigidBody.velocity.x + rigidBody.velocity.y * rigidBody.velocity.y);

		if (speed > speedLimiterComponents[i].maxVelocity)
		{
			rigidBody.velocity.x *= speedLimiterComponents[i].maxVelocity / speed;
			rigidBody.velocity.y *= speedLimiterComponents[i].maxVelocity / speed;
		}

		if (rigidBody.angularVelocity < -speedLimiterComponents[i].maxAngularVelocity)
			rigidBody.angularAcceleration = -speedLimiterComponents[i].maxAngularVelocity;
		else if (rigidBody.angularAcceleration > speedLimiterComponents[i].maxAngularVelocity)
			rigidBody.angularAcceleration = speedLimiterComponents[i].maxAngularVelocity;
	}
}
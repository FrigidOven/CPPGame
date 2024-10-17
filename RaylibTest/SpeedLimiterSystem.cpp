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
		
		float speed = Vector2Length(rigidBody.velocity);

		if (speed > speedLimiterComponents[i].maxVelocity)
		{
			rigidBody.velocity.x *= speedLimiterComponents[i].maxVelocity / speed;
			rigidBody.velocity.y *= speedLimiterComponents[i].maxVelocity / speed;

			speedLimiterComponents[i].atMaxVelocity = true;
		}
		else
		{
			speedLimiterComponents[i].atMaxVelocity = false;
		}

		if (rigidBody.angularVelocity < -speedLimiterComponents[i].maxAngularVelocity ||
			speedLimiterComponents[i].maxAngularVelocity < rigidBody.angularVelocity)
		{
			rigidBody.angularVelocity = rigidBody.angularVelocity < 0 ? -speedLimiterComponents[i].maxAngularVelocity : speedLimiterComponents[i].maxAngularVelocity;
			speedLimiterComponents[i].atMaxAngularVelocity = true;
		}
		else
		{
			speedLimiterComponents[i].atMaxAngularVelocity = false;
		}
	}
}
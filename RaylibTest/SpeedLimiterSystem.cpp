#include "ECS.h"

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
		
		// if at max velocity
		if (Vector2Length(rigidBody.velocity) >= speedLimiter.maxVelocity)
		{
			// clamp velocity
			rigidBody.velocity = Vector2ClampValue(rigidBody.velocity, 0.0f, speedLimiter.maxVelocity);

			// cancel out acceleration that is not working to decrease velocity
			if (rigidBody.velocity.x * rigidBody.acceleration.x > 0.0f)
				rigidBody.acceleration.x = 0.0f;
			if (rigidBody.velocity.y * rigidBody.acceleration.y > 0.0f)
				rigidBody.acceleration.y = 0.0f;
		}
		// if at max angular velocity
		if (rigidBody.angularVelocity >= speedLimiter.maxAngularVelocity)
		{
			// clamp angular velocity
			rigidBody.angularVelocity = Clamp(rigidBody.angularVelocity, -speedLimiter.maxAngularVelocity, speedLimiter.maxAngularVelocity);

			// cancel out angular acceleration that is not working to decrease angular velocity
			if(rigidBody.angularAcceleration * rigidBody.angularVelocity > 0.0f)
				rigidBody.angularAcceleration = 0.0f;
		}
	}
}
#include "ForceBasedSpeedLimiterSystem.h"
#include "Scene.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ForceBasedSpeedLimiterSystem::Update(Scene* scene, std::vector<ForceBasedSpeedLimiter>& forceBasedSpeedLimiters)
{
	int requiredComponentsMask = (1 << Velocity::ID) | (1 << Acceleration::ID);

	for (auto& forceBasedSpeedLimiter : forceBasedSpeedLimiters)
	{
		if ((scene->GetComponentMask(forceBasedSpeedLimiter.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Velocity& velocity = scene->GetComponent<Velocity>(forceBasedSpeedLimiter.entity);
		Acceleration& acceleration = scene->GetComponent<Acceleration>(forceBasedSpeedLimiter.entity);

		// if at max velocity
		if (Vector2Length(velocity.velocity) >= forceBasedSpeedLimiter.maxVelocity)
		{
			// clamp velocity
			velocity.velocity = Vector2ClampValue(velocity.velocity, 0.0f, forceBasedSpeedLimiter.maxVelocity);

			// cancel out acceleration that is not working to decrease velocity
			if (velocity.velocity.x * acceleration.acceleration.x > 0.0f)
				acceleration.acceleration.x = 0.0f;
			if (velocity.velocity.y * acceleration.acceleration.y > 0.0f)
				acceleration.acceleration.y = 0.0f;
		}
	}
}
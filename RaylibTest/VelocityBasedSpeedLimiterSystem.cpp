#include "VelocityBasedSpeedLimiterSystem.h"
#include "Scene.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void VelocityBasedSpeedLimiterSystem::Update(Scene* scene, std::vector<VelocityBasedSpeedLimiter>& velocityBasedSpeedLimiters)
{
	for (auto& velocityBasedSpeedLimiter : velocityBasedSpeedLimiters)
	{
		Velocity& velocity = scene->GetComponent<Velocity>(velocityBasedSpeedLimiter.entity);

		// if at max velocity
		if (Vector2Length(velocity.velocity) >= velocityBasedSpeedLimiter.maxVelocity)
		{
			// clamp velocity
			velocity.velocity = Vector2ClampValue(velocity.velocity, 0.0f, velocityBasedSpeedLimiter.maxVelocity);
		}
	}
}
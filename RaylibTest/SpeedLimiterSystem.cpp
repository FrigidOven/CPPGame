#include "SpeedLimiterSystem.h"
#include "Scene.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void SpeedLimiterSystem::Update(Scene& scene, std::vector<SpeedLimiter>& speedLimiters)
{
	int requiredComponentsMask = (1 << Velocity::ID) | (1 << Acceleration::ID);

	for (auto& speedLimiter : speedLimiters)
	{
		if ((scene.GetComponentMask(speedLimiter.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Velocity& velocity = scene.GetComponent<Velocity>(speedLimiter.entity);
		Acceleration& acceleration = scene.GetComponent<Acceleration>(speedLimiter.entity);

		// if at max velocity
		if (Vector2Length(velocity.velocity) >= speedLimiter.maxVelocity)
		{



			// cancel out acceleration that is not working to decrease velocity
			if (velocity.velocity.x * acceleration.acceleration.x > 0.0f)
				acceleration.acceleration.x = 0.0f;
			if (velocity.velocity.y * acceleration.acceleration.y > 0.0f)
				acceleration.acceleration.y = 0.0f;
		}
	}
}

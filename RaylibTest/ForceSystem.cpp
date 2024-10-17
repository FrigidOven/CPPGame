#include <vector>
#include <raylib.h>
#include<raymath.h>
#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ForceSystem::Update(Scene* scene, std::vector<Force>& forceComponents)
{
	int forceCount = static_cast<int>(forceComponents.size());

	for (int i = 0; i < forceCount; i++)
	{
		float deltaTime = GetFrameTime();

		RigidBody& rigidBody = scene->GetComponent<RigidBody>(forceComponents[i].entity);

		// compromise here, we don't want to keep applying a force if the speed is capped so we check for a SpeedLimiter component.
		bool hasSpeedLimiter = scene->HasComponent<SpeedLimiter>(forceComponents[i].entity);

		// linear acceleration
		// f = ma so a = f/m
		Vector2 deltaAcceleration = { deltaTime * forceComponents[i].force.x / rigidBody.mass, deltaTime * forceComponents[i].force.y / rigidBody.mass };

		if (hasSpeedLimiter && scene->GetComponent<SpeedLimiter>(rigidBody.entity).atMaxVelocity)
		{
			// only apply acceleration if it slows rigid body down
			if ( rigidBody.acceleration.x >= 0 && deltaAcceleration.x < 0
			   || rigidBody.acceleration.x <= 0 && deltaAcceleration.x > 0 )
			{
				rigidBody.acceleration.x += deltaAcceleration.x;
			}
			if (rigidBody.acceleration.y >= 0 && deltaAcceleration.y < 0
			  || rigidBody.acceleration.y <= 0 && deltaAcceleration.y > 0)
			{
				rigidBody.acceleration.y += deltaAcceleration.y;
			}
		}
		else
		{
			rigidBody.acceleration = Vector2Add(rigidBody.acceleration, deltaAcceleration);
		}

		// angular acceleration
		float deltaAngularAcceleration = deltaTime * forceComponents[i].angularForce / rigidBody.mass;

		if (hasSpeedLimiter && scene->GetComponent<SpeedLimiter>(rigidBody.entity).atMaxAngularVelocity)
		{
			// only apply angular acceleration if it slows rigid body down
			if (rigidBody.angularAcceleration > 0 && deltaAngularAcceleration < 0
			  || rigidBody.angularAcceleration < 0 && deltaAngularAcceleration > 0)
			{
				rigidBody.acceleration.x += deltaAcceleration.x;
			}
		}
		else
		{
			rigidBody.angularAcceleration += deltaAngularAcceleration;
		}
	}
}
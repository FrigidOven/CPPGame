#include <vector>
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

		if (!hasSpeedLimiter || !scene->GetComponent<SpeedLimiter>(forceComponents[i].entity).atMaxVelocity)
		{
			// f = ma so a = f/m
			Vector2 deltaAcceleration = { deltaTime * forceComponents[i].force.x / rigidBody.mass, deltaTime * forceComponents[i].force.y / rigidBody.mass };

			rigidBody.acceleration.x += deltaAcceleration.x;
			rigidBody.acceleration.y += deltaAcceleration.y;
		}
		if (!hasSpeedLimiter || !scene->GetComponent<SpeedLimiter>(forceComponents[i].entity).atMaxAngularVelocity)
		{
			float deltaAngularAcceleration = deltaTime * forceComponents[i].angularForce;

			rigidBody.angularAcceleration += deltaAngularAcceleration;
		}
	}
}
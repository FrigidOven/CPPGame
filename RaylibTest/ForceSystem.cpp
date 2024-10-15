#include <vector>
#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
ForceSystem::ForceSystem(Scene& scene, std::vector<Force>& forceComponents)
	: scene(scene)
	, forceComponents(forceComponents)
{
}
void ForceSystem::Update()
{
	int forceCount = static_cast<int>(forceComponents.size());

	for (int i = 0; i < forceCount; i++)
	{
		float deltaTime = GetFrameTime();

		RigidBody& rigidBody = scene.GetRigidBodyComponent(forceComponents[i].entity);


		// compromise here, we don't want to keep applying a force if the speed is capped so we check for a SpeedLimiter component.

		bool hasSpeedLimiter = scene.HasComponent(forceComponents[i].entity, ComponentType::SpeedLimiter);

		if (!hasSpeedLimiter || !scene.GetSpeedLimiterComponent(forceComponents[i].entity).atMaxVelocity)
		{
			// f = ma so a = f/m
			Vector2 deltaAcceleration = { deltaTime * forceComponents[i].force.x / rigidBody.mass, deltaTime * forceComponents[i].entity / rigidBody.mass };

			rigidBody.acceleration.x += deltaAcceleration.x;
			rigidBody.acceleration.y += deltaAcceleration.y;
		}
		if (!hasSpeedLimiter || !scene.GetSpeedLimiterComponent(forceComponents[i].entity).atMaxAngularVelocity)
		{
			float deltaAngularAcceleration = deltaTime * forceComponents[i].angularForce;

			rigidBody.angularAcceleration += deltaAngularAcceleration;
		}
	}
}
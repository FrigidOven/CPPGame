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

		// f = ma so a = f/m
		Vector2 deltaAcceleration = { deltaTime * forceComponents[i].force.x / rigidBody.mass, deltaTime * forceComponents[i].entity / rigidBody.mass };

		rigidBody.acceleration.x += deltaAcceleration.x;
		rigidBody.acceleration.y += deltaAcceleration.y;

		float deltaAngularAcceleration = deltaTime * forceComponents[i].angularForce;

		rigidBody.angularAcceleration += deltaAngularAcceleration;
	}
}
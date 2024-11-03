#include "ForceApplierSystem.h"
#include "Scene.h"

#include <raymath.h>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ForceApplierSystem::Update(Scene& scene, std::vector<ForceReceiver>& forceReceivers, float deltaTime)
{
	int requiredComponentsMask = (1 << Acceleration::ID) | (1<<Velocity::ID) | (1<<Mass::ID);

	for (auto& forceReceiver : forceReceivers)
	{	
		if ((scene.GetComponentMask(forceReceiver.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Vector2 velocity = scene.GetComponent<Velocity>(forceReceiver.entity).velocity;
		float mass = scene.GetComponent<Mass>(forceReceiver.entity).mass;

		Vector2 acceleration = Vector2Scale(forceReceiver.pushingForce, 1.0f / mass);
		Vector2 deceleration = Vector2Scale(forceReceiver.resistingForce, 1.0f / mass);

		Vector2 deltaVelocity = Vector2Scale(Vector2Add(acceleration, deceleration), deltaTime);

		// if the velocity will change directions next frame and it is due to the deceleration,
		// limit the deceleration so that it may only ever stop the velocity

		// solve deltaVelocity = acceleration * time + deceleration * time
		// where deltaVelocity = -velocity

		if (velocity.x * (velocity.x + deltaVelocity.x) < 0.0f && abs(acceleration.x) < abs(deceleration.x))
			deceleration.x = acceleration.x - velocity.x/deltaTime;

		if (velocity.y * (velocity.y + deltaVelocity.y) < 0.0f && abs(acceleration.y) < abs(deceleration.y))
			deceleration.y = acceleration.y - velocity.y/deltaTime;

		// f = ma so a = f/m
		scene.GetComponent<Acceleration>(forceReceiver.entity).acceleration = Vector2Add(acceleration, deceleration);

		// clear forces
		forceReceiver.pushingForce = Vector2Zero();
		forceReceiver.resistingForce = Vector2Zero();
	}
}
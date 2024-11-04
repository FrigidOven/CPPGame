#include "ForceApplierSystem.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ForceApplierSystem::Update(Scene& scene, std::vector<Rigidbody>& rigidbodies, float deltaTime)
{
	int requiredComponentsMask = (1 << static_cast<int>(Acceleration::ID)) | (1 << static_cast<int>(Velocity::ID));

	for (auto& rigidbody : rigidbodies)
	{	
		if ((scene.GetComponentMask(rigidbody.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Vector2 velocity = scene.GetComponent<Velocity>(rigidbody.entity).velocity;

		Vector2 acceleration = Vector2Scale(rigidbody.pushingForce, 1.0f / rigidbody.mass);
		Vector2 deceleration = Vector2Scale(rigidbody.resistingForce, 1.0f / rigidbody.mass);

		Vector2 deltaVelocity = Vector2Scale(Vector2Add(acceleration, deceleration), deltaTime);

		// if the velocity will change directions next frame and it is due to the deceleration,
		// limit the deceleration so that it may only ever stop the velocity

		// solve deltaVelocity = acceleration * time + deceleration * time
		// where deltaVelocity = -velocity
		
		if (abs(acceleration.x) < abs(deceleration.x) && velocity.x * (velocity.x + deltaVelocity.x) < 0.0f)
			deceleration.x = acceleration.x - velocity.x/deltaTime;

		if (abs(acceleration.y) < abs(deceleration.y) && velocity.y * (velocity.y + deltaVelocity.y) < 0.0f)
			deceleration.y = acceleration.y - velocity.y/deltaTime;

		// f = ma so a = f/m
		scene.GetComponent<Acceleration>(rigidbody.entity).acceleration = Vector2Add(acceleration, deceleration);

		// clear forces
		rigidbody.pushingForce = Vector2Zero();
		rigidbody.resistingForce = Vector2Zero();
	}
}
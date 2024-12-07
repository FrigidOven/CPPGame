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

		Velocity& velocity = scene.GetComponent<Velocity>(rigidbody.entity);

		Vector2 internalVelocity = velocity.internalVelocity;
		Vector2 externalVelocity = velocity.externalVelocity;

		Vector2 internalAcceleration = Vector2Scale(rigidbody.internalPushingForce, 1.0f / rigidbody.mass);
		Vector2 internalDeceleration = Vector2Scale(rigidbody.internalResistingForce, 1.0f / rigidbody.mass);

		Vector2 externalAcceleration = Vector2Scale(rigidbody.externalPushingForce, 1.0f / rigidbody.mass);
		Vector2 externalDeceleration = Vector2Scale(rigidbody.externalResistingForce, 1.0f / rigidbody.mass);

		Vector2 deltaInternalVelocity = Vector2Scale(Vector2Add(internalAcceleration, internalDeceleration), deltaTime);
		Vector2 deltaExternalVelocity = Vector2Scale(Vector2Add(externalAcceleration, externalDeceleration), deltaTime);

		// if the velocity will change directions next frame and it is due to the deceleration,
		// limit the deceleration so that it may only ever stop the velocity

		// solve deltaVelocity = acceleration * time + deceleration * time
		// where deltaVelocity = -velocity
		
		if (abs(internalAcceleration.x) < abs(internalDeceleration.x) && internalVelocity.x * (internalVelocity.x + deltaInternalVelocity.x) < 0.0f)
			internalDeceleration.x = internalAcceleration.x - internalVelocity.x/deltaTime;
		if (abs(internalAcceleration.y) < abs(internalDeceleration.y) && internalVelocity.y * (internalVelocity.y + deltaInternalVelocity.y) < 0.0f)
			internalDeceleration.y = internalAcceleration.y - internalVelocity.y/deltaTime;

		if (abs(externalAcceleration.x) < abs(externalDeceleration.x) && externalVelocity.x * (externalVelocity.x + deltaExternalVelocity.x) < 0.0f)
			externalDeceleration.x = externalAcceleration.x - externalVelocity.x / deltaTime;
		if (abs(externalAcceleration.y) < abs(externalDeceleration.y) && externalVelocity.y * (externalVelocity.y + deltaExternalVelocity.y) < 0.0f)
			externalDeceleration.y = externalAcceleration.y - externalVelocity.y / deltaTime;

		Acceleration& acceleration = scene.GetComponent<Acceleration>(rigidbody.entity);

		acceleration.internalAcceleration = Vector2Add(internalAcceleration, internalDeceleration);
		acceleration.externalAcceleration = Vector2Add(externalAcceleration, externalDeceleration);

		// clear forces
		rigidbody.internalPushingForce = Vector2Zero();
		rigidbody.internalResistingForce = Vector2Zero();
		rigidbody.externalPushingForce = Vector2Zero();
		rigidbody.externalResistingForce = Vector2Zero();
	}
}
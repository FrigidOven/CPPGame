#include "FrictionSystem.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void FrictionSystem::Update(Scene& scene, std::vector<Friction>& frictions)
{
	const float GRAVITY = -9.8f;

	int requiredComponentsMask = (1 << static_cast<int>(Rigidbody::ID)) | (1 <<  static_cast<int>(Velocity::ID));

	for (auto& friction : frictions)
	{	
		if ((scene.GetComponentMask(friction.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Velocity& velocity = scene.GetComponent<Velocity>(friction.entity);
		Rigidbody& rigidbody = scene.GetComponent<Rigidbody>(friction.entity);

		Vector2 internalFriction = Vector2Scale(Vector2Normalize(velocity.internalVelocity), friction.coefficient * GRAVITY * rigidbody.mass);
		Vector2 externalFriction = Vector2Scale(Vector2Normalize(velocity.externalVelocity), friction.coefficient * GRAVITY * rigidbody.mass);

		rigidbody.internalResistingForce = Vector2Add(rigidbody.internalResistingForce, internalFriction);
		rigidbody.externalResistingForce = Vector2Add(rigidbody.externalResistingForce, externalFriction);
	}
}

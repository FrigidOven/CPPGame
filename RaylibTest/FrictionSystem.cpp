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

		Rigidbody& rigidbody = scene.GetComponent<Rigidbody>(friction.entity);
		Vector2& velocity = scene.GetComponent<Velocity>(friction.entity).velocity;

		friction.force = Vector2Scale(Vector2Normalize(velocity), friction.coefficient * GRAVITY * rigidbody.mass);
		rigidbody.resistingForce = Vector2Add(rigidbody.resistingForce, friction.force);
	}
}

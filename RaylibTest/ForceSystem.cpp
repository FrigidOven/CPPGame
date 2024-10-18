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
	const float gravity = 9.8f;
	const float frictionCutOffVelocity = 0.1;

	for (auto& force : forceComponents)
	{
		RigidBody& rigidBody = scene->GetComponent<RigidBody>(force.entity);

		// sum internal and external forces
		Vector2 totalForce = Vector2Add(force.internalForce, force.externalForce);
		float totalAngularForce = force.internalAngularForce + force.externalAngularForce;

		// initialize friction to zero
		Vector2 frictionForce = { 0.0f, 0.0f };
		float angularFrictionForce = 0.0f;

		// only find friction if velocity is above the cut off for friction
		if (Vector2Length(rigidBody.velocity) >= frictionCutOffVelocity)
			frictionForce = Vector2Scale(rigidBody.velocity, -rigidBody.frictionCoefficient * gravity * rigidBody.mass);
		if (rigidBody.angularVelocity >= frictionCutOffVelocity)
			angularFrictionForce = Clamp(rigidBody.angularVelocity, -1, 1) * -rigidBody.frictionCoefficient * rigidBody.angularVelocity;

		// add friction
		totalForce = Vector2Add(totalForce, frictionForce);
		totalAngularForce += angularFrictionForce;

		// f = ma so a = f/m
		rigidBody.acceleration = Vector2Scale(totalForce, 1.0f / rigidBody.mass);
		rigidBody.angularAcceleration = totalAngularForce / rigidBody.mass;
	}
}
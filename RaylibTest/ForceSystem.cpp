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

	for (auto& force : forceComponents)
	{
		RigidBody& rigidBody = scene->GetComponent<RigidBody>(force.entity);

		// sum internal and external forces
		Vector2 totalForce = Vector2Add(force.internalForce, force.externalForce);
		float totalAngularForce = force.internalAngularForce + force.externalAngularForce;

		// initialize friction to 0
		Vector2 frictionForce = { 0.0f, 0.0f };
		float angularFrictionForce = 0.0f;

		// dont find friction if velocity is roughly 0
		if (Vector2Length(rigidBody.velocity) != 0)
			frictionForce = Vector2Scale(Vector2Normalize(rigidBody.velocity), -rigidBody.frictionCoefficient * gravity * rigidBody.mass);

		// dont find angular friction if angular velocity is roughly 0
		if (rigidBody.angularVelocity != 0)
			angularFrictionForce = Clamp(rigidBody.angularVelocity, -1, 1) * -rigidBody.frictionCoefficient * rigidBody.angularVelocity;

		// add friction
		totalForce = Vector2Add(totalForce, frictionForce);
		totalAngularForce += angularFrictionForce;

		// f = ma so a = f/m
		// linear acceleration
		rigidBody.acceleration = Vector2Scale(totalForce, 1.0f / rigidBody.mass);
		// angular acceleration
		rigidBody.angularAcceleration = totalAngularForce / rigidBody.mass;
	}
}
#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ForceSystem::Update(Scene* scene, std::vector<Force>& forceComponents)
{
	const float GRAVITY = 9.8f;
	const float FRICTION_CUT_OFF_VELOCITY = 0.1f;

	for (auto& force : forceComponents)
	{
		if (!scene->HasComponent<Movement>(force.entity))
		{
			force.internalForce = Vector2Zero();
			force.internalAngularForce = 0.0f;
		}

		RigidBody& rigidBody = scene->GetComponent<RigidBody>(force.entity);

		// sum internal and external forces
		Vector2 totalForce = Vector2Add(force.internalForce, force.externalForce);
		float totalAngularForce = force.internalAngularForce + force.externalAngularForce;

		// initialize friction to zero
		Vector2 frictionForce = { 0.0f, 0.0f };
		float angularFrictionForce = 0.0f;

		// only find friction if velocity is above the cut off for friction
		if (Vector2Length(rigidBody.velocity) >= FRICTION_CUT_OFF_VELOCITY)
			frictionForce = Vector2Scale(rigidBody.velocity, -rigidBody.frictionCoefficient * GRAVITY * rigidBody.mass);
		if (rigidBody.angularVelocity >= FRICTION_CUT_OFF_VELOCITY)
			angularFrictionForce = rigidBody.angularVelocity * -rigidBody.frictionCoefficient * GRAVITY * rigidBody.mass;

		// add friction
		totalForce = Vector2Add(totalForce, frictionForce);
		totalAngularForce += angularFrictionForce;

		// f = ma so a = f/m
		rigidBody.acceleration = Vector2Scale(totalForce, 1.0f / rigidBody.mass);
		rigidBody.angularAcceleration = totalAngularForce / rigidBody.mass;
	}
}
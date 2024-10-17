#include <vector>
#include <raylib.h>
#include<raymath.h>
#include "ECS.h"
#include <iostream>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ForceSystem::Update(Scene* scene, std::vector<Force>& forceComponents)
{
	int forceCount = static_cast<int>(forceComponents.size());

	const float normalForceMagnitude = 20.0f;
	const float minVelocity = 0.01f;

	for (int i = 0; i < forceCount; i++)
	{
		RigidBody& rigidBody = scene->GetComponent<RigidBody>(forceComponents[i].entity);

		// sum internal and external forces
		Vector2 totalForce = Vector2Add(forceComponents[i].internalForce, forceComponents[i].externalForce);
		float totalAngularForce = forceComponents[i].internalAngularForce + forceComponents[i].externalAngularForce;

		Vector2 frictionForce = { 0.0f, 0.0f };
		float angularFrictionForce = 0.0f;


		float velocityMagnitude = Vector2Length(rigidBody.velocity);

		// dont find friction if velocity is roughly 0
		if (-minVelocity <= velocityMagnitude && velocityMagnitude <= minVelocity)
		{
			rigidBody.velocity = Vector2Zero();
			rigidBody.acceleration = Vector2Zero();
		}
		else
			frictionForce = Vector2Scale(Vector2Normalize(rigidBody.velocity), -rigidBody.frictionCoefficient * normalForceMagnitude);

		// dont find friction if angular velocity is roughly 0
		if (-minVelocity <= rigidBody.angularVelocity && rigidBody.angularVelocity <= minVelocity)
			rigidBody.angularVelocity = 0.0f;
		else
			angularFrictionForce = Clamp(rigidBody.angularVelocity, -1, 1) * -rigidBody.frictionCoefficient * normalForceMagnitude;

		// add friction
		totalForce = Vector2Add(totalForce, frictionForce);
		totalAngularForce += angularFrictionForce;

		std::cout << "Total Force is: <" << totalForce.x << ", " << totalForce.y << ">\n";

		// f = ma so a = f/m

		// linear acceleration
		rigidBody.acceleration = Vector2Scale(totalForce, 1.0f / rigidBody.mass);
		// angular acceleration
		rigidBody.angularAcceleration = totalAngularForce / rigidBody.mass;
	}
}
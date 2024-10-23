#include "ForceSystem.h"
#include "Scene.h"

#include <raymath.h>

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ForceSystem::Update(Scene* scene, std::vector<Force>& forces, float deltaTime)
{
	int requiredComponentsMask = (1 << Acceleration::ID) | (1<<Velocity::ID) | (1<<Mass::ID);

	for (auto& force : forces)
	{	
		if ((scene->GetComponentMask(force.entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		Vector2 pushingForces = force.force;
		Vector2 resistingForces = Vector2Zero();

		// get movement force if it exists
		if (scene->HasComponent<ForceBasedMovement>(force.entity))
			pushingForces = Vector2Add(pushingForces, scene->GetComponent<ForceBasedMovement>(force.entity).force);

		// get friction force if it exists
		if (scene->HasComponent<Friction>(force.entity))
			resistingForces = Vector2Add(resistingForces, scene->GetComponent<Friction>(force.entity).force);

		// get stopping force if it exists
		if (scene->HasComponent<StoppingForce>(force.entity))
			resistingForces = Vector2Add(resistingForces, scene->GetComponent<StoppingForce>(force.entity).force);

		Vector2 velocity = scene->GetComponent<Velocity>(force.entity).velocity;
		float mass = scene->GetComponent<Mass>(force.entity).mass;

		Vector2 acceleration = Vector2Scale(pushingForces, 1.0f / mass);
		Vector2 deceleration = Vector2Scale(resistingForces, 1.0f / mass);

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
		scene->GetComponent<Acceleration>(force.entity).acceleration = Vector2Add(acceleration, deceleration);
	}
}
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "Scene.h"
#include "Systems.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void VelocitySystem::Update(Scene* scene, std::vector<RigidBody>& rigidBodyComponents)
{
	for (auto& rigidBody : rigidBodyComponents)
	{
		float deltaTime = GetFrameTime();

		// find displacement
		Vector2 displacement = Vector2Scale(rigidBody.velocity, deltaTime);
		float angularDisplacement = rigidBody.angularVelocity * deltaTime;

		Spatial& spatial = scene->GetComponent<Spatial>(rigidBody.entity);

		// add to position
		spatial.position = Vector2Add(spatial.position, displacement);
		spatial.rotation += angularDisplacement;
	}
}
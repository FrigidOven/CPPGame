#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void StoppedSystem::Update(Scene* scene, std::vector<Stopped>& stoppedComponents)
{
	for (auto& stop : stoppedComponents)
	{
		if (stop.isForceBased)
			scene->GetComponent<Force>(stop.entity).internalForce = Vector2Zero();
		else
			scene->GetComponent<RigidBody>(stop.entity).velocity = Vector2Zero();
	}
}
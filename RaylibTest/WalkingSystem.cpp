#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void WalkingSystem::Update(Scene* scene, std::vector<Walking>& walkingComponents)
{
	for (auto& walk : walkingComponents)
	{
		if (walk.isForceBased)
			scene->GetComponent<Force>(walk.entity).internalForce = walk.direction;
		else
			scene->GetComponent<RigidBody>(walk.entity).velocity = walk.direction;
	}
}
#include "ECS.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ActionSystem::Update(Scene* scene, std::vector<Action>& actions)
{
	for (auto& action : actions)
	{
		action.command->Execute(scene, action.entity);
	}
	while (!actions.empty())
	{
		scene->RemoveComponent<Action>(actions.back().entity);
	}
}
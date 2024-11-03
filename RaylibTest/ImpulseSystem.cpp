#include "ImpulseSystem.h"
#include "Scene.h"

#include <raymath.h>
/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ImpulseSystem::Update(Scene& scene, std::vector<Impulse>& impulses, float deltaTime)
{
	int requiredComponentsMask = (1 << ForceReceiver::ID);

	for (size_t i = 0; i < impulses.size(); i++)
	{
		if ((scene.GetComponentMask(impulses[i].entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		if (impulses[i].durration <= 0.0f)
		{
			scene.RemoveComponent<Impulse>(impulses[i].entity);
			i--;
		}
		else
		{
			Vector2& pushingForce = scene.GetComponent<ForceReceiver>(impulses[i].entity).pushingForce;
			pushingForce = Vector2Add(pushingForce, impulses[i].force);
			impulses[i].durration -= deltaTime;
		}
	}
}

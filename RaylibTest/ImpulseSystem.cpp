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

		Vector2& pushingForce = scene.GetComponent<ForceReceiver>(impulses[i].entity).pushingForce;
		pushingForce = Vector2Add(pushingForce, Vector2Scale(impulses[i].force, 1.0f / deltaTime));
		scene.RemoveComponent<Impulse>(impulses[i].entity);
		i--;
	}
}

#include "ImpulseSystem.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
void ImpulseSystem::Update(Scene& scene, std::vector<Impulse>& impulses, float deltaTime)
{
	int requiredComponentsMask = (1 << static_cast<int>(Rigidbody::ID));

	for (size_t i = 0; i < impulses.size(); i++)
	{
		if ((scene.GetComponentMask(impulses[i].entity) & requiredComponentsMask) != requiredComponentsMask)
			continue;

		// add accumulated force back since it is wiped away each frame.
		Vector2 impulseForce = Vector2Add(Vector2Scale(impulses[i].forcePerSecond, impulses[i].duration - impulses[i].timer), Vector2Scale(impulses[i].forcePerSecond, deltaTime));
		Vector2& pushingForce = scene.GetComponent<Rigidbody>(impulses[i].entity).pushingForce;
		pushingForce = Vector2Add(pushingForce, impulses[i].forcePerSecond);
		
		impulses[i].timer -= deltaTime;
		if (impulses[i].timer <= 0.0f)
		{
			scene.RemoveComponent<Impulse>(impulses[i].entity);
			i--;
		}
	}
}

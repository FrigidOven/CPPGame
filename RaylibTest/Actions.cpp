#include "ECS.h"

void MovementAction::Execute(Scene* scene, int entityId)
{
	scene->GetComponent<Force>(entityId).internalForce = force;
}
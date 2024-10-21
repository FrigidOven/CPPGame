#include "ECS.h"

void MovementCommand::Execute(Scene* scene, int entityId)
{
	scene->GetComponent<Force>(entityId).internalForce = force;
}
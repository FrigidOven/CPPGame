#pragma once

#include "VelocityBasedMovementController.h"

#include <vector>

class Scene;

class VelocityBasedMovementControllerSystem
{
public:
	void Update(Scene* scene, std::vector<VelocityBasedMovementController>& velocityBasedMovementControllers);
};
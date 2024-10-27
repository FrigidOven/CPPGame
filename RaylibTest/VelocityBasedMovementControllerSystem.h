#pragma once

#include "Scene.h"
#include "VelocityBasedMovementController.h"

#include <vector>

class VelocityBasedMovementControllerSystem
{
public:
	void Update(Scene& scene, std::vector<VelocityBasedMovementController>& velocityBasedMovementControllers);
};
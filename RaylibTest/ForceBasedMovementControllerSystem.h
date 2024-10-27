#pragma once

#include "Scene.h"
#include "ForceBasedMovementController.h"

#include <vector>

class ForceBasedMovementControllerSystem
{
public:
	void Update(Scene& scene, std::vector<ForceBasedMovementController>& forceBasedMovementControllers);
};
#pragma once

#include "ForceBasedMovementController.h"

#include <vector>

class Scene;

class ForceBasedMovementControllerSystem
{
public:
	void Update(Scene* scene, std::vector<ForceBasedMovementController>& forceBasedMovementControllers);
};
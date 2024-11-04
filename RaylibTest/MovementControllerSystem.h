#pragma once

#include "Scene.h"
#include "Controller.h"

#include <vector>

class MovementControllerSystem
{
public:
	void Update(Scene& scene, std::vector<MovementController>& controllers);
};
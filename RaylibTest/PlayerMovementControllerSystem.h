#pragma once

#include "Scene.h"
#include "Controller.h"

#include <vector>

class PlayerMovementControllerSystem
{
public:
	void Update(Scene& scene, std::vector<Controller>& controllers);
};
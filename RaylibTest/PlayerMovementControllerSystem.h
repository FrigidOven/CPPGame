#pragma once

#include "Scene.h"

class PlayerMovementControllerSystem
{
public:
	void Update(Scene& scene, std::vector<Controller>& controllers);
};
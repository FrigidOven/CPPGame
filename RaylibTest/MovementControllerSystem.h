#pragma once

#include "Scene.h"

class MovementControllerSystem
{
public:
	void Update(Scene& scene, std::vector<MovementController>& controllers);
};
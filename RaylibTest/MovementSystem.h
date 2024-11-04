#pragma once

#include "Scene.h"

class MovementSystem
{
public:
	void Update(Scene& scene, std::vector<Movement>& movements);
};
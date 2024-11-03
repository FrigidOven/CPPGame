#pragma once

#include "Scene.h"
#include "Movement.h"

#include <vector>

class MovementSystem
{
public:
	void Update(Scene& scene, std::vector<Movement>& movements);
};
#pragma once

#include "Scene.h"
#include "StoppingForce.h"

#include <vector>

class StoppingForceSystem
{
public:
	void Update(Scene& scene, std::vector<StoppingForce>& stoppingForces);
};
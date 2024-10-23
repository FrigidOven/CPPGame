#pragma once

#include "StoppingForce.h"

#include <vector>

class Scene;

class StoppingForceSystem
{
public:
	void Update(Scene* scene, std::vector<StoppingForce>& stoppingForces);
};
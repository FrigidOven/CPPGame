#pragma once

#include "Scene.h"
#include "Acceleration.h"

#include <vector>

class AccelerationSystem
{
public:
	void Update(Scene& scene, std::vector<Acceleration>& accelerations, float deltaTime);
};
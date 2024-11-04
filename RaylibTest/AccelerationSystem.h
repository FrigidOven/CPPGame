#pragma once

#include "Scene.h"

class AccelerationSystem
{
public:
	void Update(Scene& scene, std::vector<Acceleration>& accelerations, float deltaTime);
};
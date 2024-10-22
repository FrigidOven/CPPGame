#pragma once

#include "Acceleration.h"

#include <vector>

class Scene;

class AccelerationSystem
{
public:
	void Update(Scene* scene, std::vector<Acceleration>& accelerations);
};
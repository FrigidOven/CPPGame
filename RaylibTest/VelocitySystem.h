#pragma once

#include "Velocity.h"

#include <vector>

class Scene;

class VelocitySystem
{
public:
	void Update(Scene* scene, std::vector<Velocity>& velocities);
};
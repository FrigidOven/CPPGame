#pragma once

#include "Scene.h"
#include "Velocity.h"

#include <vector>

class VelocitySystem
{
public:
	void Update(Scene& scene, std::vector<Velocity>& velocities, float deltaTime);
};
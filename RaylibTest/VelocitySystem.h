#pragma once

#include "Scene.h"

class VelocitySystem
{
public:
	void Update(Scene& scene, std::vector<Velocity>& velocities, float deltaTime);
};
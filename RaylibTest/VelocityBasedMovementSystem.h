#pragma once

#include "VelocityBasedMovement.h"

#include <vector>

class Scene;

class VelocityBasedMovementSystem
{
public:
	void Update(Scene* scene, std::vector<VelocityBasedMovement>& velocityBasedMovements);
};
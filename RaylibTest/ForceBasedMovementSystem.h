#pragma once

#include "ForceBasedMovement.h"

#include <vector>

class Scene;

class ForceBasedMovementSystem
{
public:
	void Update(Scene* scene, std::vector<ForceBasedMovement>& forceBasedMovements);
};
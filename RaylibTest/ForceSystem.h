#pragma once

#include "Scene.h"
#include "Force.h"

#include <vector>

class ForceSystem
{
public:
	void Update(Scene& scene, std::vector<Force>& forces, float deltaTime);
};
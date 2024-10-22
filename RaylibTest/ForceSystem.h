#pragma once

#include "Force.h"

#include <vector>

class Scene;

class ForceSystem
{
public:
	void Update(Scene* scene, std::vector<Force>& forces);
};
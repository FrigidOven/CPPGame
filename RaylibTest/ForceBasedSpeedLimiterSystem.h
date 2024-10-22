#pragma once

#include "ForceBasedSpeedLimiter.h"

#include <vector>

class Scene;

class ForceBasedSpeedLimiterSystem
{
public:
	void Update(Scene* scene, std::vector<ForceBasedSpeedLimiter>& forceBasedSpeedLimiters);
};
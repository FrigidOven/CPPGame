#pragma once

#include "Scene.h"
#include "ForceBasedSpeedLimiter.h"

#include <vector>

class ForceBasedSpeedLimiterSystem
{
public:
	void Update(Scene& scene, std::vector<ForceBasedSpeedLimiter>& forceBasedSpeedLimiters);
};
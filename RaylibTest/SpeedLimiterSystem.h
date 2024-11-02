#pragma once

#include "Scene.h"
#include "SpeedLimiter.h"

#include <vector>

class SpeedLimiterSystem
{
public:
	void Update(Scene& scene, std::vector<SpeedLimiter>& speedLimiters);
};
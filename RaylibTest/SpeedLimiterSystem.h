#pragma once

#include "Scene.h"

class SpeedLimiterSystem
{
public:
	void Update(Scene& scene, std::vector<SpeedLimiter>& speedLimiters);
};
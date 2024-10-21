#pragma once

#include "VelocityBasedSpeedLimiter.h"

#include <vector>

class Scene;

class VelocityBasedSpeedLimiterSystem
{
public:
	void Update(Scene* scene, std::vector<VelocityBasedSpeedLimiter>& velocityBasedSpeedLimiters);
};
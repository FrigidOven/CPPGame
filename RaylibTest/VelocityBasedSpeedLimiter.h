#pragma once

#include "Component.h"
#include <raylib.h>

struct VelocityBasedSpeedLimiter : Component
{
	static const int ID = 10;

	float maxVelocity;

	VelocityBasedSpeedLimiter(int entityId, float maxVelocity)
		: maxVelocity(maxVelocity)
	{
		entity = entityId;
	}
};
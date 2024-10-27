#pragma once

#include "Component.h"
#include <raylib.h>

struct ForceBasedSpeedLimiter : Component
{
	static const int ID = 7;

	float maxVelocity;

	ForceBasedSpeedLimiter(int entityId, float maxVelocity)
		: maxVelocity(maxVelocity)
	{
		entity = entityId;
	}
};
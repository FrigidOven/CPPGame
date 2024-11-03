#pragma once

#include "Component.h"
#include <raylib.h>

struct SpeedLimiter : Component
{
	static const int ID = 13;

	float maxVelocity;

	SpeedLimiter(int entityId, float maxVelocity)
		: maxVelocity(maxVelocity)
	{
		entity = entityId;
	}
};
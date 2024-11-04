#pragma once

#include "Component.h"
#include <raylib.h>

struct SpeedLimiter : Component
{
	static const ComponentID ID = ComponentID::SpeedLimiter;

	float maxVelocity;

	SpeedLimiter(int entityId, float maxVelocity)
		: maxVelocity(maxVelocity)
	{
		entity = entityId;
	}
};
#pragma once

#include "Component.h"
#include "Tags.h"
#include <raylib.h>

enum class MovementMode
{
	ForceBased,
	VelocityBased
};

struct MovementController : Component
{
	static const int ID = 11;

	MovementMode mode;
	float magnitude;
	Direction requestedDirection;

	MovementController(int entityId, MovementMode mode, float magnitude)
		: mode(mode)
		, magnitude(magnitude)
		, requestedDirection(Direction::None)
	{
		entity = entityId;
	}
};
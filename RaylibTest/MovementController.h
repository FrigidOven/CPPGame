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
	static const ComponentID ID = ComponentID::MovementController;

	MovementMode mode;
	float magnitude;
	float topSpeed;
	Direction requestedDirection;

	MovementController(int entityId, MovementMode mode, float magnitude, float topSpeed)
		: mode(mode)
		, magnitude(magnitude)
		, topSpeed(topSpeed)
		, requestedDirection(Direction::None)
	{
		entity = entityId;
	}
};
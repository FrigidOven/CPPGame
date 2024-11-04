#pragma once

#include "Component.h"
#include "MovementController.h"
#include <raylib.h>

struct Movement : Component
{
	static const ComponentID ID = ComponentID::Movement;

	MovementMode mode;
	Vector2 direction;

	Movement(int entityId, MovementMode mode, Vector2 direction)
		: mode(mode)
		, direction(direction)
	{
		entity = entityId;
	}
};
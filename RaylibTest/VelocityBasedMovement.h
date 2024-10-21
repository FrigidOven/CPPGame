#pragma once

#include "Component.h"
#include <raylib.h>

struct VelocityBasedMovement : Component
{
	static const int ID = 12;

	Vector2 direction;

	VelocityBasedMovement(int entityId, Vector2 direction)
		: direction(direction)
	{
		entity = entityId;
	}
};
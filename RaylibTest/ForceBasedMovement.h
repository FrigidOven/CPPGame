#pragma once

#include "Component.h"
#include <raylib.h>

struct ForceBasedMovement : Component
{
	static const int ID = 9;

	Vector2 direction;

	ForceBasedMovement(int entityId, Vector2 direction)
		: direction(direction)
	{
		entity = entityId;
	}
};
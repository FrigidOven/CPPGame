#pragma once

#include "Component.h"
#include <raylib.h>

struct ForceBasedMovement : Component
{
	static const int ID = 9;

	Vector2 force;

	ForceBasedMovement(int entityId, Vector2 force)
		: force(force)
	{
		entity = entityId;
	}
};
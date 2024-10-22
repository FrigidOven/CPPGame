#pragma once

#include "Component.h"
#include <raylib.h>

struct Force : Component
{
	static const int ID = 7;

	Vector2 force;

	Force(int entityId, Vector2 force)
		: force(force)
	{
		entity = entityId;
	}
};
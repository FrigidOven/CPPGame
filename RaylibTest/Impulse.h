#pragma once

#include "Component.h"
#include <raylib.h>

struct Impulse : Component
{
	static const int ID = 9;

	Vector2 force;

	Impulse(int entityId, Vector2 force)
		: force(force)
	{
		entity = entityId;
	}
};
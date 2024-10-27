#pragma once

#include "Component.h"
#include <raylib.h>

struct Velocity : Component
{
	static const int ID = 2;

	Vector2 velocity;

	Velocity(int entityId, Vector2 velocity)
		: velocity(velocity)
	{
		entity = entityId;
	}
};
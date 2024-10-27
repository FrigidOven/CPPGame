#pragma once

#include "Component.h"
#include <raylib.h>

struct VelocityBasedMovement : Component
{
	static const int ID = 10;

	Vector2 velocity;

	VelocityBasedMovement(int entityId, Vector2 velocity)
		: velocity(velocity)
	{
		entity = entityId;
	}
};
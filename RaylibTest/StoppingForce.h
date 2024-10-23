#pragma once

#include "Component.h"
#include <raylib.h>

struct StoppingForce : Component
{
	static const int ID = 16;

	Vector2 force;

	StoppingForce(int entityId, Vector2 force)
		: force(force)
	{
		entity = entityId;
	}
};
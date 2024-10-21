#pragma once

#include "Component.h"
#include <raylib.h>

struct Friction : Component
{
	static const int ID = 8;

	float coefficient;
	Vector2 force;

	Friction(int entityId, Vector2 force)
		: force(force)
	{
		entity = entityId;
	}
};
#pragma once

#include "Component.h"
#include <raylib.h>

struct Impulse : Component
{
	static const int ID = 10;

	Vector2 force;
	float durration;

	Impulse(int entityId, Vector2 force, float durration)
		: force(force)
		, durration(durration)
	{
		entity = entityId;
	}
};
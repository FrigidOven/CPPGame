#pragma once

#include "Component.h"
#include <raylib.h>

struct Impulse : Component
{
	static const ComponentID ID = ComponentID::Impulse;

	Vector2 force;

	Impulse(int entityId, Vector2 force)
		: force(force)
	{
		entity = entityId;
	}
};
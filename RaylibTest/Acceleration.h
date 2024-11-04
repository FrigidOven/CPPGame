#pragma once

#include "Component.h"
#include <raylib.h>

struct Acceleration : Component
{
	static const ComponentID ID = ComponentID::Acceleration;

	Vector2 acceleration;

	Acceleration(int entityId, Vector2 acceleration)
		: acceleration(acceleration)
	{
		entity = entityId;
	}
};
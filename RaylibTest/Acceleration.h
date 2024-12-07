#pragma once

#include "Component.h"
#include <raylib.h>

struct Acceleration : Component
{
	static const ComponentID ID = ComponentID::Acceleration;

	Vector2 internalAcceleration;
	Vector2 externalAcceleration;

	Acceleration(int entityId)
		: internalAcceleration(Vector2Zero())
		, externalAcceleration(Vector2Zero())
	{
		entity = entityId;
	}
};
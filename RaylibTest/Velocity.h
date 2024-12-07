#pragma once

#include "Component.h"
#include <raylib.h>

struct Velocity : Component
{
	static const ComponentID ID = ComponentID::Velocity;

	Vector2 internalVelocity;
	Vector2 externalVelocity;

	Velocity(int entityId)
		: internalVelocity(Vector2Zero())
		, externalVelocity(Vector2Zero())
	{
		entity = entityId;
	}
};
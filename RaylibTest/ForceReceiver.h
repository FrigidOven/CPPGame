#pragma once

#include "Component.h"
#include <raylib.h>

struct ForceReceiver : Component
{
	static const int ID = 7;

	Vector2 resistingForce;
	Vector2 pushingForce;

	ForceReceiver(int entityId)
		: resistingForce(Vector2Zero())
		, pushingForce(Vector2Zero())
	{
		entity = entityId;
	}
};
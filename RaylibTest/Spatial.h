#pragma once

#include "Component.h"
#include <raylib.h>

struct Spatial : Component
{
	static const int ID = 1;

	Vector2 position;
	float rotation;

	Spatial(int entityId, Vector2 position, float rotation)
		: position(position)
		, rotation(rotation)
	{
		entity = entityId;
	}
};
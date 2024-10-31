#pragma once

#include "Component.h"
#include <raylib.h>

enum class Orientation
{
	Up,
	Left,
	Down,
	Right
};

struct Direction : Component
{
	static const int ID = 17;

	Orientation direction;

	Direction(int entityId, Orientation direction)
		: direction(direction)
	{
		entity = entityId;
	}
};
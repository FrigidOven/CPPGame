#pragma once

#include "Component.h"
#include <raylib.h>

struct Friction : Component
{
	static const int ID = 8;

	float coefficient;

	Friction(int entityId, float coefficient)
		: coefficient(coefficient)
	{
		entity = entityId;
	}
};
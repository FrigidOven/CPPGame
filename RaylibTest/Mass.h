#pragma once

#include "Component.h"
#include <raylib.h>

struct Mass : Component
{
	static const int ID = 6;

	float mass;

	Mass(int entityId, float mass)
		: mass(mass)
	{
		entity = entityId;
	}
};
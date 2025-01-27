#pragma once

#include "Component.h"

#include <raylib.h>
#include <raymath.h>

struct Friction : Component
{
	static const ComponentID ID = ComponentID::Friction;

	float coefficient;

	Friction(int entityId, float coefficient)
		: coefficient(coefficient)
	{
		entity = entityId;
	}
};
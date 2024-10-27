#pragma once

#include "Component.h"

#include <raylib.h>
#include <raymath.h>

struct Friction : Component
{
	static const int ID = 6;

	float coefficient;
	Vector2 force;

	Friction(int entityId, float coefficient)
		: coefficient(coefficient)
		, force(Vector2Zero())
	{
		entity = entityId;
	}
};
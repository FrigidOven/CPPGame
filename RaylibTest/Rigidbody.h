#pragma once

#include "Component.h"
#include <raylib.h>

struct Rigidbody : Component
{
	static const ComponentID ID = ComponentID::Rigidbody;

	float mass;
	Vector2 resistingForce;
	Vector2 pushingForce;

	Rigidbody(int entityId, float mass)
		: mass(mass)
		, resistingForce(Vector2Zero())
		, pushingForce(Vector2Zero())
	{
		entity = entityId;
	}
};
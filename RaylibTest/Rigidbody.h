#pragma once

#include "Component.h"
#include <raylib.h>

struct Rigidbody : Component
{
	static const ComponentID ID = ComponentID::Rigidbody;

	float mass;
	Vector2 internalPushingForce;
	Vector2 externalPushingForce;
	Vector2 internalResistingForce;
	Vector2 externalResistingForce;

	Rigidbody(int entityId, float mass)
		: mass(mass)
		, internalPushingForce(Vector2Zero())
		, externalPushingForce(Vector2Zero())
		, internalResistingForce(Vector2Zero())
		, externalResistingForce(Vector2Zero())
	{
		entity = entityId;
	}
};
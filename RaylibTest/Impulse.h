#pragma once

#include "Component.h"
#include <raylib.h>

struct Impulse : Component
{
	static const ComponentID ID = ComponentID::Impulse;

	Vector2 forcePerSecond;
	float duration;
	float timer;

	Impulse(int entityId, Vector2 forcePerSecond, float duration)
		: forcePerSecond(forcePerSecond)
		, duration(duration)
		, timer(duration)
	{
		entity = entityId;
	}
};
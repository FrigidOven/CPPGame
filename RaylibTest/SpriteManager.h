#pragma once

#include "Component.h"
#include "Sprite.h"
#include <raylib.h>

struct SpriteManager : Component
{
	static const int ID = 15;

	SpriteOrientation orientation;
	SpriteState state;

	SpriteManager(int entityId, SpriteOrientation orientation, SpriteState state)
		: orientation(orientation)
		, state(state)
	{
		entity = entityId;
	}
};
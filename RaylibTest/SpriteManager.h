#pragma once

#include "Component.h"
#include "SpriteAtlas.h"
#include <raylib.h>

struct SpriteManager : Component
{
	static const int ID = 13;

	SpriteState state;

	SpriteManager(int entityId, SpriteState state)
		: state(state)
	{
		entity = entityId;
	}
};
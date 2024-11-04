#pragma once

#include "Component.h"
#include <raylib.h>

struct SpriteManager : Component
{
	static const int ID = 13;

	SpriteManager(int entityId)
	{
		entity = entityId;
	}
};
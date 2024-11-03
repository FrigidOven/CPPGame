#pragma once

#include "Component.h"
#include <raylib.h>

struct SpriteManager : Component
{
	static const int ID = 14;

	SpriteManager(int entityId)
	{
		entity = entityId;
	}
};
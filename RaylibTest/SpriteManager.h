#pragma once

#include "Component.h"
#include <raylib.h>

struct SpriteManager : Component
{
	static const ComponentID ID = ComponentID::SpriteManager;

	SpriteManager(int entityId)
	{
		entity = entityId;
	}
};
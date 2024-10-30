#pragma once

#include "Component.h"
#include "SpriteData.h"
#include <raylib.h>

struct Sprite : Component
{
	static const int ID = 1;

	int layer;
	Frame frame;

	Sprite(int entityId, int layer, Frame frame)
		: layer(layer)
		, frame(frame)
	{
		entity = entityId;
	}
};
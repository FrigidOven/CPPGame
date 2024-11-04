#pragma once

#include "Component.h"
#include <raylib.h>

struct Sprite : Component
{
	static const ComponentID ID = ComponentID::Sprite;

	int layer;

	Texture2D* source;
	Rectangle sourceRect;

	float xScale;
	float yScale;

	int frameCount;
	int currentFrame;
	float timer;
	float fps;

	Sprite(int entityId, int layer, Texture2D* source, Rectangle sourceRect, float xScale, float yScale, int frameCount, int currentFrame, float fps)
		: layer(layer)
		, source(source)
		, sourceRect(sourceRect)
		, xScale(xScale)
		, yScale(yScale)
		, frameCount(frameCount)
		, currentFrame(currentFrame)
		, timer(0.0f)
		, fps(fps)
	{
		entity = entityId;
	}
};
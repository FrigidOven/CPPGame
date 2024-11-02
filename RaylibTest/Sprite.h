#pragma once

#include "Component.h"
#include <raylib.h>

struct Sprite : Component
{
	static const int ID = 2;

	int layer;

	Texture2D* source;
	Rectangle sourceRect;

	float destWidth;
	float destHeight;

	int frameCount;
	int currentFrame;
	float timer;
	float fps;

	Sprite(int entityId, int layer, Texture2D* source, Rectangle sourceRect, float destWidth, float destHeight, int frameCount, int currentFrame, float fps)
		: layer(layer)
		, source(source)
		, sourceRect(sourceRect)
		, destWidth(destWidth)
		, destHeight(destHeight)
		, frameCount(frameCount)
		, currentFrame(currentFrame)
		, timer(0.0f)
		, fps(fps)
	{
		entity = entityId;
	}
};
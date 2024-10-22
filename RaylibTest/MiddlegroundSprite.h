#pragma once

#include "Component.h"
#include <raylib.h>

struct MiddlegroundSprite : Component
{
	static const int ID = 2;

	Texture2D* source;
	Rectangle sourceRect;

	float destWidth;
	float destHeight;

	int frameCount;
	int currentFrame;
	float timer;
	float fps;

	MiddlegroundSprite(int entityId, Texture2D* source, Rectangle sourceRect, float destWidth, float destHeight, int frameCount, int currentFrame, float fps)
		: source(source)
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
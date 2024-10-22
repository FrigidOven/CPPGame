#pragma once

#include "Component.h"
#include <raylib.h>

struct ForegroundSprite : Component
{
	static const int ID = 3;

	Texture2D* source;
	Rectangle sourceRect;

	float destWidth;
	float destHeight;

	int frameCount;
	int currentFrame;
	float timer;
	float fps;

	ForegroundSprite(int entityId, Texture2D* source, Rectangle sourceRect, float destWidth, float destHeight, int frameCount, int currentFrame, float fps)
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
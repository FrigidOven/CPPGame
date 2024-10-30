#pragma once

#include "Component.h"
#include "AnimationData.h"
#include <raylib.h>

struct Animation : Component
{
	static const int ID = 15;

	AnimationData* animationData;
	int currentFrame;
	float timer;

	Animation(int entityId, AnimationData* animationData, int currentFrame, float timer)
		: animationData(animationData)
		, currentFrame(currentFrame)
		, timer(timer)
	{
		entity = entityId;
	}
};
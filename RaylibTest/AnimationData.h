#pragma once

#include <raylib.h>
#include <array>
#include "SpriteData.h"

struct AnimationData
{
	bool loops;
	virtual int GetFrameCount() = 0;
	virtual Frame& GetFrame(int index) = 0;
};

template<int frameCount>
struct CustomFrameLayout : AnimationData
{
	std::array<Frame, frameCount> frames;

	int GetFrameCount() override
	{
		return frameCount;
	}
	Frame& GetFrame(int& index) override
	{
		return frames[index];
	}

	CustomFrameLayout(std::array<Frame, frameCount> frames)
		: frames(frames)
	{
	}
};

template<int frameCount>
struct HorizontalFrameLayout : AnimationData
{
	std::array<Frame, frameCount> frames;

	int GetFrameCount() override
	{
		return frameCount;
	}
	Frame& GetFrame(int& index) override
	{
		return frames[index];
	}

	HorizontalFrameLayout(const Texture2D* source, Rectangle initialSourceRect, Vector2 destWidthHeight, Vector2 offset, float frameDurration, Color tint)
	{

	}
};

struct AnimationReader
{
	AnimationData* animationData;
	int currentFrame;
	float timer;

	void Update(float deltaTime)
	{
		float frameDurration = animationData->GetFrame(currentFrame).durration;
		int frameCount = animationData->GetFrameCount();

		timer += deltaTime;

		if (timer >= frameDurration)
		{
			timer = 0.0f;
			currentFrame++;
		}

		if (currentFrame >= frameCount)
			currentFrame = animationData->loops ? currentFrame % frameCount : frameCount - 1;
	}
	Frame& GetFrame()
	{
		return animationData->GetFrame(currentFrame);
	}
};
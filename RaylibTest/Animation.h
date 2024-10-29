#pragma once

#include <raylib.h>
#include <array>

struct Animation
{
	bool loops;
	virtual int GetFrameCount() = 0;
	virtual Frame& GetFrame(int index) = 0;
};

template<int frameCount>
struct SpriteAnimation : Animation
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
};

struct AnimationReader
{
	Texture2D* source;
	Animation* animation;
	int currentFrame;
	float timer;

	void Update(float deltaTime)
	{
		float frameDurration = animation->GetFrame(currentFrame).durration;
		int frameCount = animation->GetFrameCount();

		timer += deltaTime;

		if (timer >= frameDurration)
		{
			timer = 0.0f;
			currentFrame++;
		}

		if (currentFrame >= frameCount)
			currentFrame = animation->loops ? currentFrame % frameCount : frameCount - 1;
	}
	Frame& GetFrame()
	{
		return animation->GetFrame(currentFrame);
	}
};

struct Frame
{
	Rectangle sourceRect;
	Vector2 offset;
	float durration;
	Color tint;
};
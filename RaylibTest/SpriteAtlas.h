#pragma once

#include "Direction.h"
#include <unordered_map>

enum class SpriteState
{
	Idle,
	Moving
};

struct StateOrientationHash
{
	std::size_t operator () (const std::pair<SpriteState, Orientation>& stateOrientation) const
	{
		return std::hash<SpriteState>{}(stateOrientation.first) ^ std::hash<Orientation>{}(stateOrientation.second);
	}
};

class SpriteAtlas
{
public:
	virtual int GetYPos(SpriteState state, Orientation orientation) = 0;
	virtual int GetFrameCount(SpriteState state, Orientation orientation) = 0;
	virtual float GetFPS(SpriteState state, Orientation orientation) = 0;
};

class PlayerSpriteAtlas : public SpriteAtlas
{
private:
	std::unordered_map<Orientation, int> orientationYPos;
	std::unordered_map<SpriteState, int> stateYPos;
	std::unordered_map<std::pair<SpriteState, Orientation>, int, StateOrientationHash> stateOrientationFrameCounts;
	std::unordered_map<std::pair<SpriteState, Orientation>, float, StateOrientationHash> stateOrientationFPS;

public:
	PlayerSpriteAtlas();
	
	static const int WIDTH = 32;
	static const int HEIGHT = 32;

	int GetYPos(SpriteState state, Orientation orientation) override;
    int GetFrameCount(SpriteState state, Orientation orientation) override;
	float GetFPS(SpriteState state, Orientation orientation) override;
};
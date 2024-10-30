#pragma once

#include <unordered_map>

enum class SpriteOrientation
{
	Up,
	Left,
	Down,
	Right
};

enum class SpriteState
{
	Idle,
	Moving
};

struct StateOrientationHash
{
	std::size_t operator () (const std::pair<SpriteState, SpriteOrientation>& stateOrientation) const
	{
		return std::hash<SpriteState>{}(stateOrientation.first) ^ std::hash<SpriteOrientation>{}(stateOrientation.second);
	}
};

class SpriteAtlas
{
public:
	virtual int GetYPos(SpriteState state, SpriteOrientation orientation) = 0;
	virtual int GetFrameCount(SpriteState state, SpriteOrientation orientation) = 0;
	virtual float GetFPS(SpriteState state, SpriteOrientation orientation) = 0;
};

class PlayerSpriteAtlas : public SpriteAtlas
{
private:
	std::unordered_map<SpriteOrientation, int> orientationYPos;
	std::unordered_map<SpriteState, int> stateYPos;
	std::unordered_map<std::pair<SpriteState, SpriteOrientation>, int, StateOrientationHash> stateOrientationFrameCounts;
	std::unordered_map<std::pair<SpriteState, SpriteOrientation>, float, StateOrientationHash> stateOrientationFPS;

public:
	PlayerSpriteAtlas();
	
	static const int WIDTH = 32;
	static const int HEIGHT = 32;

	int GetYPos(SpriteState state, SpriteOrientation orientation) override;
    int GetFrameCount(SpriteState state, SpriteOrientation orientation) override;
	float GetFPS(SpriteState state, SpriteOrientation orientation) override;
};
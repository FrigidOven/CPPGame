#pragma once

#include "Tags.h"
#include <unordered_map>


struct StateDirectionHash
{
	std::size_t operator () (const std::pair<State, Direction>& stateDirection) const
	{
		return std::hash<State>{}(stateDirection.first) ^ std::hash<Direction>{}(stateDirection.second);
	}
};

class SpriteAtlas
{
public:
	virtual int GetYPos(State state, Direction direction) = 0;
	virtual int GetFrameCount(State state, Direction direction) = 0;
	virtual float GetFPS(State state, Direction direction) = 0;
};

class PlayerSpriteAtlas : public SpriteAtlas
{
private:
	std::unordered_map<Direction, int> directionYPos;
	std::unordered_map<State, int> stateYPos;
	std::unordered_map<std::pair<State, Direction>, int, StateDirectionHash> stateDirectionFrameCounts;
	std::unordered_map<std::pair<State, Direction>, float, StateDirectionHash> stateDirectionFPS;

public:
	PlayerSpriteAtlas();
	
	static const int WIDTH = 32;
	static const int HEIGHT = 32;

	int GetYPos(State state, Direction direction) override;
    int GetFrameCount(State state, Direction direction) override;
	float GetFPS(State state, Direction direction) override;
};
#include "SpriteAtlas.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
PlayerSpriteAtlas::PlayerSpriteAtlas()
{
	// direction y pos
	directionYPos[Direction::Up] = 0;
	directionYPos[Direction::Left] = HEIGHT;
	directionYPos[Direction::Down] = 2 * HEIGHT;
	directionYPos[Direction::Right] = 3 * HEIGHT;

	// idle y pos
	stateYPos[State::Idle] = 0;
	// moving y pos
	stateYPos[State::Moving] = 4 * HEIGHT;

	// idle frame counts
	stateDirectionFrameCounts[std::make_pair(State::Idle, Direction::Up)] = 2;
	stateDirectionFrameCounts[std::make_pair(State::Idle, Direction::Left)] = 2;
	stateDirectionFrameCounts[std::make_pair(State::Idle, Direction::Down)] = 2;
	stateDirectionFrameCounts[std::make_pair(State::Idle, Direction::Right)] = 2;
	// idle fps
	stateDirectionFPS[std::make_pair(State::Idle, Direction::Up)] = 2;
	stateDirectionFPS[std::make_pair(State::Idle, Direction::Left)] = 2;
	stateDirectionFPS[std::make_pair(State::Idle, Direction::Down)] = 2;
	stateDirectionFPS[std::make_pair(State::Idle, Direction::Right)] = 2;

	// moving frame counts
	stateDirectionFrameCounts[std::make_pair(State::Moving, Direction::Up)] = 8;
	stateDirectionFrameCounts[std::make_pair(State::Moving, Direction::Left)] = 8;
	stateDirectionFrameCounts[std::make_pair(State::Moving, Direction::Down)] = 8;
	stateDirectionFrameCounts[std::make_pair(State::Moving, Direction::Right)] = 8;
	// moving fps
	stateDirectionFPS[std::make_pair(State::Moving, Direction::Up)] = 12;
	stateDirectionFPS[std::make_pair(State::Moving, Direction::Left)] = 12;
	stateDirectionFPS[std::make_pair(State::Moving, Direction::Down)] = 12;
	stateDirectionFPS[std::make_pair(State::Moving, Direction::Right)] = 12;
}
int PlayerSpriteAtlas::GetYPos(State state, Direction direction)
{
	return stateYPos[state] + directionYPos[direction];
}
int PlayerSpriteAtlas::GetFrameCount(State state, Direction direction)
{
	return stateDirectionFrameCounts[std::make_pair(state, direction)];
}
float PlayerSpriteAtlas::GetFPS(State state, Direction direction)
{
	return stateDirectionFPS[std::make_pair(state, direction)];
}
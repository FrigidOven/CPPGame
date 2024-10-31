#include "SpriteAtlas.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
PlayerSpriteAtlas::PlayerSpriteAtlas()
{
	// orientation y pos
	orientationYPos[Orientation::Up] = 0;
	orientationYPos[Orientation::Left] = HEIGHT;
	orientationYPos[Orientation::Down] = 2 * HEIGHT;
	orientationYPos[Orientation::Right] = 3 * HEIGHT;

	// idle y pos
	stateYPos[SpriteState::Idle] = 0;
	// moving y pos
	stateYPos[SpriteState::Moving] = 4 * HEIGHT;

	// idle frame counts
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, Orientation::Up)] = 2;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, Orientation::Left)] = 2;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, Orientation::Down)] = 2;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, Orientation::Right)] = 2;
	// idle fps
	stateOrientationFPS[std::make_pair(SpriteState::Idle, Orientation::Up)] = 2;
	stateOrientationFPS[std::make_pair(SpriteState::Idle, Orientation::Left)] = 2;
	stateOrientationFPS[std::make_pair(SpriteState::Idle, Orientation::Down)] = 2;
	stateOrientationFPS[std::make_pair(SpriteState::Idle, Orientation::Right)] = 2;

	// moving frame counts
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, Orientation::Up)] = 8;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, Orientation::Left)] = 8;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, Orientation::Down)] = 8;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, Orientation::Right)] = 8;
	// moving fps
	stateOrientationFPS[std::make_pair(SpriteState::Moving, Orientation::Up)] = 14;
	stateOrientationFPS[std::make_pair(SpriteState::Moving, Orientation::Left)] = 14;
	stateOrientationFPS[std::make_pair(SpriteState::Moving, Orientation::Down)] = 14;
	stateOrientationFPS[std::make_pair(SpriteState::Moving, Orientation::Right)] = 14;
}
int PlayerSpriteAtlas::GetYPos(SpriteState state, Orientation orientation)
{
	return stateYPos[state] + orientationYPos[orientation];
}
int PlayerSpriteAtlas::GetFrameCount(SpriteState state, Orientation orientation)
{
	return stateOrientationFrameCounts[std::make_pair(state, orientation)];
}
float PlayerSpriteAtlas::GetFPS(SpriteState state, Orientation orientation)
{
	return stateOrientationFPS[std::make_pair(state, orientation)];
}
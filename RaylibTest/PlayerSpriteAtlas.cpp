#include "SpriteAtlas.h"

/*
===================================================================================================
 Public Functions
===================================================================================================
*/
PlayerSpriteAtlas::PlayerSpriteAtlas()
{
	// orientation y pos
	orientationYPos[SpriteOrientation::Up] = 0;
	orientationYPos[SpriteOrientation::Left] = HEIGHT;
	orientationYPos[SpriteOrientation::Down] = 2 * HEIGHT;
	orientationYPos[SpriteOrientation::Right] = 3 * HEIGHT;

	// idle y pos
	stateYPos[SpriteState::Idle] = 0;
	// moving y pos
	stateYPos[SpriteState::Moving] = 4 * HEIGHT;

	// idle frame counts
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, SpriteOrientation::Up)] = 2;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, SpriteOrientation::Left)] = 2;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, SpriteOrientation::Down)] = 2;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, SpriteOrientation::Right)] = 2;
	// idle fps
	stateOrientationFPS[std::make_pair(SpriteState::Idle, SpriteOrientation::Up)] = 2;
	stateOrientationFPS[std::make_pair(SpriteState::Idle, SpriteOrientation::Left)] = 2;
	stateOrientationFPS[std::make_pair(SpriteState::Idle, SpriteOrientation::Down)] = 2;
	stateOrientationFPS[std::make_pair(SpriteState::Idle, SpriteOrientation::Right)] = 2;

	// moving frame counts
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, SpriteOrientation::Up)] = 8;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, SpriteOrientation::Left)] = 8;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, SpriteOrientation::Down)] = 8;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, SpriteOrientation::Right)] = 8;
	// moving fps
	stateOrientationFPS[std::make_pair(SpriteState::Moving, SpriteOrientation::Up)] = 14;
	stateOrientationFPS[std::make_pair(SpriteState::Moving, SpriteOrientation::Left)] = 14;
	stateOrientationFPS[std::make_pair(SpriteState::Moving, SpriteOrientation::Down)] = 14;
	stateOrientationFPS[std::make_pair(SpriteState::Moving, SpriteOrientation::Right)] = 14;
}
int PlayerSpriteAtlas::GetYPos(SpriteState state, SpriteOrientation orientation)
{
	return stateYPos[state] + orientationYPos[orientation];
}
int PlayerSpriteAtlas::GetFrameCount(SpriteState state, SpriteOrientation orientation)
{
	return stateOrientationFrameCounts[std::make_pair(state, orientation)];
}
float PlayerSpriteAtlas::GetFPS(SpriteState state, SpriteOrientation orientation)
{
	return stateOrientationFPS[std::make_pair(state, orientation)];
}
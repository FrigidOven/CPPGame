#include "Sprite.h"

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
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, SpriteOrientation::Up)] = 1;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, SpriteOrientation::Left)] = 1;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, SpriteOrientation::Down)] = 1;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Idle, SpriteOrientation::Right)] = 1;
	// idle fps
	stateOrientationFPS[std::make_pair(SpriteState::Idle, SpriteOrientation::Up)] = 1;
	stateOrientationFPS[std::make_pair(SpriteState::Idle, SpriteOrientation::Left)] = 1;
	stateOrientationFPS[std::make_pair(SpriteState::Idle, SpriteOrientation::Down)] = 1;
	stateOrientationFPS[std::make_pair(SpriteState::Idle, SpriteOrientation::Right)] = 1;

	// moving frame counts
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, SpriteOrientation::Up)] = 6;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, SpriteOrientation::Left)] = 4;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, SpriteOrientation::Down)] = 6;
	stateOrientationFrameCounts[std::make_pair(SpriteState::Moving, SpriteOrientation::Right)] = 4;
	// moving fps
	stateOrientationFPS[std::make_pair(SpriteState::Moving, SpriteOrientation::Up)] = 7.5f;
	stateOrientationFPS[std::make_pair(SpriteState::Moving, SpriteOrientation::Left)] = 5;
	stateOrientationFPS[std::make_pair(SpriteState::Moving, SpriteOrientation::Down)] = 7.5f;
	stateOrientationFPS[std::make_pair(SpriteState::Moving, SpriteOrientation::Right)] = 5;
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
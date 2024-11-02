#pragma once
#include "raylib.h"
#include "raymath.h"

enum class EntityGroup
{
	None,
	Engine,
	Surface,
	Player
};
enum class EntityType
{
	None,
	GrassSurface,
	Player,
	Camera
};
enum class Direction
{
	None,
	Up,
	Left,
	Down,
	Right,
	UpLeft,
	UpRight,
	DownLeft,
	DownRight
};
inline Vector2 DirectionToVector2(Direction direction)
{
	switch (direction)
	{
	case Direction::Up:
		return Vector2(0.0f, -1.0f);
	case Direction::Left:
		return Vector2(-1.0f, 0.0f);
	case Direction::Down:
		return Vector2(0.0f, 1.0f);
	case Direction::Right:
		return Vector2(1.0f, 0.0f);
	case Direction::UpLeft:
		return Vector2(-0.707107f, -0.707107f);
	case Direction::UpRight:
		return Vector2(0.707107f, -0.707107f);
	case Direction::DownLeft:
		return Vector2(-0.707107f, 0.707107f);
	case Direction::DownRight:
		return Vector2(0.707107f, 0.707107f);
	 default: // none
		return Vector2Zero();
	}
}

enum class State
{
	Idle, // no "None", default state is idle.
	Moving
};
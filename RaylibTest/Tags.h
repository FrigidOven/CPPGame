#pragma once

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
	DownRight,
};
enum class State
{
	Idle, // no "None", default state is idle.
	Moving
};
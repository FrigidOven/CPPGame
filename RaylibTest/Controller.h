#pragma once

#include "Component.h"
#include "Input.h"

struct Controller : Component
{
private:
	static inline int PLAYER_COUNT = 0; // used for reading correct gamepad, player1, player2, etc.

public:
	static const int ID = 3;

	const int playerNumber;
	Input up;
	Input left;
	Input down;
	Input right;
	// all other inputs go here

	Controller(int entityId, Input up, Input left, Input down, Input right)
		: playerNumber(PLAYER_COUNT++)
		, up(up)
		, left(left)
		, down(down)
		, right(right)
	{
		entity = entityId;
	}
};
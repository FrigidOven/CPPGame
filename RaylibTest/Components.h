#pragma once

#include <raylib.h>
#include <raymath.h>

#include "Input.h"

/*
* =================================================
*	BASE COMPONENT
* =================================================
*/
struct Component
{
	static const int COMPONENT_COUNT = 7;
	int entity;
};


/*
* =================================================
*	SPATIAL COMPONENT
* =================================================
*/
struct Spatial : Component
{
	static const int ID = 0;

	Vector2 position;
	float rotation;

	Spatial(int entityId, Vector2 position, float rotation)
		: position(position)
		, rotation(rotation)
	{
		entity = entityId;
	}
};

/*
* =================================================
* SPRITE COMPONENT
* =================================================
*/
struct Sprite : Component
{
	static const int ID = 1;

	Texture2D* source;
	Rectangle sourceRect;
	float width;
	float height;
	int frameCount;
	float timer;
	float fps;

	Sprite(int entityId, Texture2D* source, Rectangle sourceRect, float width, float height, int frameCount, float fps)
		: source(source)
		, sourceRect(sourceRect)
		, width(width), height(height)
		, frameCount(frameCount)
		, timer(0.0f)
		, fps(fps)
	{
		entity = entityId;
	}
};

/*
* =================================================
*	RIGID BODY COMPONENT
* =================================================
*/
struct RigidBody : Component
{
	static const int ID = 2;

	float mass;
	Vector2 velocity;
	float angularVelocity;
	Vector2 acceleration;
	float angularAcceleration;
	float frictionCoefficient;

	RigidBody(int entityId, float mass, Vector2 velocity, float angularVelocity, Vector2 acceleration, float angularAcceleration, float frictionCoefficient)
		: mass(mass)
		, velocity(velocity)
		, angularVelocity(angularVelocity)
		, acceleration(acceleration)
		, angularAcceleration(angularAcceleration)
		, frictionCoefficient(frictionCoefficient)
	{
		entity = entityId;
	}
};

/*
* =================================================
* FORCE COMPONENT
* =================================================
*/
struct Force : Component
{
	static const int ID = 3;

	Vector2 externalForce;
	Vector2 internalForce;

	float externalAngularForce;
	float internalAngularForce;


	Force(int entityId, Vector2 externalForce, Vector2 internalForce, float externalAngularForce, float internalAngularForce)
		: externalForce(externalForce)
		, internalForce(internalForce)
		, externalAngularForce(externalAngularForce)
		, internalAngularForce(internalAngularForce)
	{
		entity = entityId;
	}
};

/*
* =================================================
* SPEED LIMITER COMPONENT
* =================================================
*/
struct SpeedLimiter : Component
{
	static const int ID = 4;

	float maxVelocity;
	float maxAngularVelocity;

	SpeedLimiter(int entityId, float maxVelocity, float maxAngularVelocity)
		: maxVelocity(maxVelocity)
		, maxAngularVelocity(maxAngularVelocity)
	{
		entity = entityId;
	}
};

/*
* =================================================
* PLAYER INPUT LISTENER COMPONENT
* =================================================
*/
struct PlayerInputListener : Component
{
	static const int ID = 5;

	Input up;
	Input left;
	Input down;
	Input right;

	InputListener inputListener;

	PlayerInputListener(int entityId, Input up, Input left, Input down, Input right)
		: up(up)
		, left(left)
		, down(down)
		, right(right)
	{
		entity = entityId;

		inputListener.ListenForInput(up);
		inputListener.ListenForInput(left);
		inputListener.ListenForInput(down);
		inputListener.ListenForInput(right);
	}
};

/*
* =================================================
* MOVEMENT COMPONENT
* =================================================
*/
struct Movement : Component
{
	static const int ID = 6;

	bool isForceBased;
	Vector2 direction;

	Movement(int entityId, bool isForceBased, Vector2 direction)
		: isForceBased(isForceBased)
		, direction(direction)
	{
		entity = entityId;
	}
};
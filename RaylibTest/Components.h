#pragma once

#include <raylib.h>
#include <raymath.h>

/*
* =================================================
*	BASE COMPONENT
* =================================================
*/
struct Component
{
	static const int COMPONENT_COUNT = 6;
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

	Sprite(int entityId, Texture2D* source, Rectangle sourceRect, float width, float height, int frameCount, float timer, float fps)
		: source(source)
		, sourceRect(sourceRect)
		, width(width), height(height)
		, frameCount(frameCount)
		, timer(timer)
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

	KeyboardKey upKey;
	KeyboardKey leftKey;
	KeyboardKey downKey;
	KeyboardKey rightKey;

	bool upIsDown;
	bool downIsDown;
	bool leftIsDown;
	bool rightIsDown;

	PlayerInputListener(int entityId, KeyboardKey upKey, KeyboardKey leftKey, KeyboardKey downKey, KeyboardKey rightKey)
		: upKey(upKey)
		, leftKey(leftKey)
		, downKey(downKey)
		, rightKey(rightKey)
		, upIsDown(false)
		, downIsDown(false)
		, leftIsDown(false)
		, rightIsDown(false)
	{
		entity = entityId;
	}
};
#pragma once

enum class ComponentID
{
	Tag,
	Spatial,
	Sprite,
	Controller,
	Velocity,
	Acceleration,
	Rigidbody,
	Friction,
	Impulse,
	MovementController,
	Movement,
	SpeedLimiter,
	SpriteManager,
	CameraManager,
	FollowCamera,
	COMPONENT_COUNT
};

struct Component
{
	int entity;
};
#pragma once

#include <vector>

#include "Components.h"

class Scene;

/*
* =================================================
* SPRITE RENDERER SYSTEM
* =================================================
*/
class SpriteRendererSystem
{
private:
	void UpdateSprite(Sprite& sprite);

public:
	void Draw(Scene* scene, std::vector<Sprite>& spriteComponents);
};

/*
* =================================================
* FORCE SYSTEM
* =================================================
*/
class ForceSystem
{
public:
	void Update(Scene* scene, std::vector<Force>& forceComponents);
};

/*
* =================================================
* ACCELERATION SYSTEM
* =================================================
*/
class AccelerationSystem
{
public:
	void Update(Scene* scene, std::vector<RigidBody>& rigidBodyComponents);
};

/*
* =================================================
* SPEED LIMITER SYSTEM
* =================================================
*/
class SpeedLimiterSystem
{
public:
	void Update(Scene* scene, std::vector<SpeedLimiter>& speedLimiterComponents);
};

/*
* =================================================
* VELOCITY SYSTEM
* =================================================
*/
class VelocitySystem
{
public:
	void Update(Scene* scene, std::vector<RigidBody>& rigidBodyComponents);
};

/*
* =================================================
* INPUT SYSTEM
* =================================================
*/
class InputSystem
{
private:
	void RemoveUpButtons();
	void AddDownButtons();

	InputMode inputMode;

	void UpdatePlayerInputListeners(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents);

public:
	std::vector<KeyboardKey> keyboardKeys;
	std::vector<GamepadButton> gamepadButtons;
	std::vector<MouseButton> mouseButtons;

	InputSystem(InputMode inputMode);
	void Update(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents);
};

/*
* =================================================
* WALKING SYSTEM
* =================================================
*/
class WalkingSystem
{
public:
	void Update(Scene* scene, std::vector<Walking>& walkingComponents);
};

/*
* =================================================
* STOPPED SYSTEM
* =================================================
*/
class StoppedSystem
{
public:
	void Update(Scene* scene, std::vector<Stopped>& stoppedComponents);
};

/*
* =================================================
* PLAYER ACTION SYSTEM
* =================================================
*/
class PlayerActionSystem
{
private:
	void WalkUp(Scene* scene, PlayerInputListener& playerInputListener);
	void WalkLeft(Scene* scene, PlayerInputListener& playerInputListener);
	void WalkDown(Scene* scene, PlayerInputListener& playerInputListener);
	void WalkRight(Scene* scene, PlayerInputListener& playerInputListener);

	void Stop(Scene* scene, PlayerInputListener& playerInputListener);

public:
	void Update(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents);
};
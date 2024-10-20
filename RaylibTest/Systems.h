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
	std::vector<KeyboardKey> keyboardKeys;
	std::vector<GamepadButton> gamepadButtons;
	std::vector<MouseButton> mouseButton;

	InputMode inputMode;

	void RemoveKeys();
	void AddKeys();

	bool CheckInput(Input input);

	void UpdatePlayerInputListeners(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents);

public:
	InputSystem(InputMode inputMode);
	void Update(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents);
};

/*
* =================================================
* PLAYER ACTION SYSTEM
* =================================================
*/
class PlayerActionSystem
{
public:
	void Update(Scene* scene, std::vector<PlayerInputListener>& playerInputListenerComponents);
};

/*
* =================================================
* ACTION SYSTEM
* =================================================
*/
class ActionSystem
{
public:
	void Update(Scene* scene, std::vector<Action>& actions);
};
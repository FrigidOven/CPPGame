#ifndef ENTITY
#define ENTITY

#include <raylib.h>
#include <vector>

/*
===================================================================================================
 Entity
===================================================================================================
*/
struct Entity
{
	int id; // Unique ID for the entity
	int componentMask; // Bit mask for components

	Entity(int id, int componentMask)
		: id(id)
		, componentMask(componentMask)
	{
	}
};

/*
===================================================================================================
 Enums
===================================================================================================
*/

enum class  ComponentType
{
	NUMBER_OF_COMPONENTS = 6,
	Spatial = 1,								// 0b0000_0000_0000_0000_0000_0000_0000_0001
	Sprite = 2,								// 0b0000_0000_0000_0000_0000_0000_0000_0010
	RigidBody = 4,							// 0b0000_0000_0000_0000_0000_0000_0000_0100
	Force = 8,								// 0b0000_0000_0000_0000_0000_0000_0000_1000
	SpeedLimiter = 16,					// 0b0000_0000_0000_0000_0000_0000_0001_0000
	PlayerInputListener = 32	// 0b0000_0000_0000_0000_0000_0000_0010_0000
};

enum InputMode
{
	Default = 0
};

/*
===================================================================================================
 Components
===================================================================================================
*/

struct Spatial
{
	int entity;
	Vector2 position;
	float rotation;

	Spatial(int entityId, Vector2 position, int rotation)
		: entity(entityId)
		, position(position)
		, rotation(rotation)
	{
	}
	void SetPosition(Vector2 newPosition)
	{
		position = newPosition;
	}
	void Move(Vector2 distance)
	{
		position.x += distance.x;
		position.y += distance.y;
	}
	void SetRotation(float newRotation)
	{
		rotation = newRotation;
	}
	void Rotate(float angle)
	{
		rotation += angle;
	}
};

struct Sprite
{
	int entity;
	Texture2D* source;
	Rectangle sourceRect;
	float width;
	float height;
	int frameCount;
	float timer;
	float fps;

	Sprite(int entityId, Texture2D* source, Rectangle sourceRect, float width, float height, int frameCount, float timer, float fps)
		: entity(entityId)
		, source(source)
		, sourceRect(sourceRect)
		, width(width)
		, height(height)
		, frameCount(frameCount)
		, timer(timer)
		, fps(fps)
	{
	}
};
struct RigidBody
{
	int entity;
	float mass;
	Vector2 velocity;
	float angularVelocity;
	Vector2 acceleration;
	float angularAcceleration;

	RigidBody(int entityId, float mass, Vector2 velocity, float angularVelocity, Vector2 acceleration, float angularAcceleration)
		: entity(entityId)
		, mass(mass)
		, velocity(velocity)
		, angularVelocity(angularVelocity)
		, acceleration(acceleration)
		, angularAcceleration(angularAcceleration)
	{
	}
};
struct Force
{
	int entity;
	Vector2 force;
	float angularForce;

	Force(int entityId, Vector2 force, float angularForce)
		: entity(entityId)
		, force(force)
		, angularForce(angularForce)
	{
	}
};
struct SpeedLimiter
{
	int entity;
	float maxVelocity;
	float maxAngularVelocity;
	bool atMaxVelocity;
	bool atMaxAngularVelocity;

	SpeedLimiter(int entityId, float maxVelocity, float maxAngularVelocity)
		: entity(entityId)
		, maxVelocity(maxVelocity)
		, maxAngularVelocity(maxAngularVelocity)
		, atMaxVelocity(false)
		, atMaxAngularVelocity(false)
	{
	}
};

struct PlayerInputListener
{
	int entity;

	KeyboardKey upKey;
	KeyboardKey downKey;
	KeyboardKey leftKey;
	KeyboardKey rightKey;

	bool upIsDown;
	bool downIsDown;
	bool leftIsDown;
	bool rightIsDown;

	PlayerInputListener(int entityId, KeyboardKey upKey, KeyboardKey downKey, KeyboardKey leftKey, KeyboardKey rightKey)
		: entity(entityId)
		, upKey(upKey)
		, downKey(downKey)
		, leftKey(leftKey)
		, rightKey(rightKey)
		, upIsDown(false)
		, downIsDown(false)
		, leftIsDown(false)
		, rightIsDown(false)
	{
	}
};

/*
===================================================================================================
 Systems
===================================================================================================
*/

class Scene;

class SpriteRendererSystem
{
private:
	void UpdateSprite(Sprite& sprite);

public:
	void Draw(Scene* scene, std::vector<Sprite>& spriteComponents);
};

class RigidBodySystem
{
public:
	void Update(Scene* scene, std::vector<RigidBody>& rigidBodyComponents);
};

class ForceSystem
{
public:
	void Update(Scene* scene, std::vector<Force>& forceComponents);
};
class SpeedLimiterSystem
{
public:
	void Update(Scene* scene, std::vector<SpeedLimiter>& speedLimiterComponents);
};

class InputSystem
{
private:
	InputMode inputMode;

	void UpdatePlayerInputListeners(Scene* scene, std::vector<PlayerInputListener> playerInputListenerComponents);

public:
	void Update(Scene* scene, std::vector<PlayerInputListener> playerInputListenerComponents);
};

/*
===================================================================================================
 Scene
===================================================================================================
*/

class Scene
{
private:

	std::vector<Entity> entities;
	std::vector<int> components; // holds indecies into component lists for each entity

	std::vector<Spatial> spatialComponents;
	std::vector<Sprite> spriteComponents;
	std::vector<RigidBody> rigidBodyComponents;
	std::vector<Force> forceComponents;
	std::vector<SpeedLimiter> speedLimiterComponents;
	std::vector<PlayerInputListener> playerInputListenerComponents;

	SpriteRendererSystem& spriteRendererSystem;
	RigidBodySystem& rigidBodySystem;
	ForceSystem& forceSystem;
	SpeedLimiterSystem& speedLimiterSystem;
	InputSystem& inputSystem;

	int ComponentIdOffset(ComponentType componentType);

	template<typename T>
	bool AddComponent(int entityId, ComponentType componentType, std::vector<T>& componentList);

public:
	Scene(SpriteRendererSystem& spriteRendererSystem,
				RigidBodySystem& rigidBodySystem,
				ForceSystem& forceSystem,
				SpeedLimiterSystem& speedLimiterSystem,
				InputSystem& inputSystem);

	int CreateEntity();
	void Update();

	bool AddSpatialComponent(int entityId, Vector2 position, float rotation);
	bool AddSpriteComponent(int entityId, Texture2D* texture, Rectangle sourceRect, float width, float height, int frameCount, float fps);
	bool AddRigidBodyComponent(int entityId, float mass, Vector2 velocity, float angularVelocity, Vector2 acceleration, float angularAcceleration);
	bool AddForceComponent(int entityId, Vector2 force, float angularForce);
	bool AddSpeedLimiterComponent(int entityId, float maxVelocity, float maxAngularVelocity);
	bool AddPlayerInputListenerComponent(int entityId, KeyboardKey upKey, KeyboardKey downKey, KeyboardKey leftKey, KeyboardKey rightKey);

	bool RemoveSpatialComponent(int entityId);
	bool RemoveSpriteComponent(int entityId);
	bool RemoveRigidBodyComponent(int entityId);
	bool RemoveForceComponent(int entityId);
	bool RemoveSpeedLimiterComponent(int entityId);
	bool RemovePlayerInputListenerComponent(int entityId);

	Spatial& GetSpatialComponent(int entityId);
	Sprite& GetSpriteComponent(int entityId);
	RigidBody& GetRigidBodyComponent(int entityId);
	Force& GetForceComponent(int entityId);
	SpeedLimiter& GetSpeedLimiterComponent(int entityId);
	PlayerInputListener& GetPlayerInputListenerComponent(int entityId);

	bool HasComponent(int entityId, ComponentType componentType);
};
#endif
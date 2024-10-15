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
 Component Types
===================================================================================================
*/

enum class ComponentType
{
	NUMBER_OF_COMPONENTS = 4,
	Spatial = 1,
	Sprite = 2,
	RigidBody = 4,
	Force = 8,
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
};

struct PlayerMovementController
{
	int entity;

};

/*
===================================================================================================
 Systems
===================================================================================================
*/
class Scene;
class SpriteRendererSystem;
class RigidBodySystem;


class Scene
{
private:

	std::vector<int> components; // holds indecies into component lists for each entity

	SpriteRendererSystem* spriteRendererSystem;
	RigidBodySystem* rigidBodySystem;

	std::vector<Entity> entities;

	std::vector<Spatial> spatialComponents;
	std::vector<Sprite> spriteComponents;
	std::vector<RigidBody> rigidBodyComponents;

	int ComponentIdOffset(ComponentType componentType);

	template<typename T>
	bool AddComponent(int entityId, ComponentType componentType, std::vector<T>& componentList);

public:
	Scene();
	int CreateEntity();
	void Update();

	bool AddSpatialComponent(int entityId, Vector2 position, float rotation);
	bool AddSpriteComponent(int entityId, Texture2D* texture, Rectangle sourceRect, float width, float height, int frameCount, float fps);
	bool AddRigidBodyComponent(int entityId, float mass, Vector2 velocity, float angularVelocity, Vector2 acceleration, float angularAcceleration);

	bool RemoveSpatialComponent(int entityId);
	bool RemoveSpriteComponent(int entityId);
	bool RemoveRigidBodyComponent(int entityId);

	Spatial& GetSpatialComponent(int entityId);
	Sprite& GetSpriteComponent(int entityId);
	RigidBody& GetRigidBodyComponent(int entityId);

	bool HasComponent(int entityId, ComponentType componentType);
};
class SpriteRendererSystem
{
private:
	Scene& scene;
	std::vector<Sprite>& spriteComponents;

	void UpdateSprite(Sprite& sprite);

public:
	SpriteRendererSystem(Scene& scene, std::vector<Sprite>& spriteComponents);
	void Draw();
};
class RigidBodySystem
{
private:
	Scene& scene;
	std::vector<RigidBody>& rigidBodyComponents;

public:
	RigidBodySystem(Scene& scene, std::vector<RigidBody>& rigidBodyComponents);
	void Update();
};
#endif
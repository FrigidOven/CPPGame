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
	NUMBER_OF_COMPONENTS = 3,
	Spatial = 1,
	Sprite = 2,
	Velocity = 4
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

struct Velocity
{
	int entity;
	Vector2 velocity;
	float angularVelocity;

	Velocity(int entityId, Vector2 velocity, float angularVelocity)
		: entity(entityId)
		, velocity(velocity)
		, angularVelocity(angularVelocity)
	{
	}
};

/*
===================================================================================================
 Systems
===================================================================================================
*/
class Scene;
class SpriteRendererSystem;
class VelocitySystem;


class Scene
{
private:

	std::vector<int> components; // holds indecies into component lists for each entity

	SpriteRendererSystem* spriteRendererSystem;
	VelocitySystem* velocitySystem;

	std::vector<Entity> entities;

	std::vector<Spatial> spatialComponents;
	std::vector<Sprite> spriteComponents;
	std::vector<Velocity> velocityComponents;

	int ComponentIdOffset(ComponentType componentType);

	template<typename T>
	bool AddComponent(int entityId, ComponentType componentType, std::vector<T>& componentList);

public:
	Scene();
	int CreateEntity();
	void Update();

	bool AddSpatialComponent(int entityId, Vector2 position, float rotation);
	bool AddSpriteComponent(int entityId, Texture2D* texture, Rectangle sourceRect, float width, float height, int frameCount, float fps);
	bool AddVelocityComponent(int entityId, Vector2 velocity, float angularVelocity);

	bool RemoveSpatialComponent(int entityId);
	bool RemoveSpriteComponent(int entityId);
	bool RemoveVelocityComponent(int entityId);

	Spatial& GetSpatialComponent(int entityId);
	Sprite& GetSpriteComponent(int entityId);
	Velocity& GetVelocityComponent(int entityId);

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
class VelocitySystem
{
private:
	Scene& scene;
	std::vector<Velocity>& velocityComponents;

public:
	VelocitySystem(Scene& scene, std::vector<Velocity>& velocityComponents);
	void Update();
};
#endif
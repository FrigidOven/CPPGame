#ifndef ENTITY
#define ENTITY

#include <raylib.h>
#include <vector>
#include <unordered_map>

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

enum InputMode
{
	Default = 0
};

/*
===================================================================================================
 Components
===================================================================================================
*/
struct Component
{
	static const int COMPONENT_COUNT = 6;
	int entity;
};
struct Spatial : Component
{
	static const int ID = 1; // 0b0000_0000_0000_0000_0000_0000_0000_0001

	Vector2 position;
	float rotation;

	Spatial(int entityId, Vector2 position, float rotation)
		: position(position)
		, rotation(rotation)
	{
		entity = entityId;
	}
};
struct Sprite : Component
{
	static const int ID = 2; // 0b0000_0000_0000_0000_0000_0000_0000_0010

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

struct RigidBody : Component
{
	static const int ID = 4; // 0b0000_0000_0000_0000_0000_0000_0000_0100

	float mass;
	Vector2 velocity;
	float angularVelocity;
	Vector2 acceleration;
	float angularAcceleration;

	RigidBody(int entityId, float mass, Vector2 velocity, float angularVelocity, Vector2 acceleration, float angularAcceleration)
		: mass(mass)
		, velocity(velocity)
		, angularVelocity(angularVelocity)
		, acceleration(acceleration)
		, angularAcceleration(angularAcceleration)
	{
		entity = entityId;
	}
};

struct Force : Component
{
	static const int ID = 8; // 0b0000_0000_0000_0000_0000_0000_0000_1000

	Vector2 force;
	float angularForce;

	Force(int entityId, Vector2 force, float angularForce)
		: force(force)
		, angularForce(angularForce)
	{ 
		entity = entityId; 
	}
};
struct SpeedLimiter : Component
{
	static const int ID = 16; // 0b0000_0000_0000_0000_0000_0000_0001_0000

	float maxVelocity;
	float maxAngularVelocity;
	bool atMaxVelocity;
	bool atMaxAngularVelocity;

	SpeedLimiter(int entityId, float maxVelocity, float maxAngularVelocity)
		: maxVelocity(maxVelocity)
		, maxAngularVelocity(maxAngularVelocity)
		, atMaxVelocity(false)
		, atMaxAngularVelocity(false)
	{
		entity = entityId;
	}
};

struct PlayerInputListener : Component
{
	static const int ID = 32; // 0b0000_0000_0000_0000_0000_0000_0010_0000

	KeyboardKey upKey;
	KeyboardKey downKey;
	KeyboardKey leftKey;
	KeyboardKey rightKey;

	bool upIsDown;
	bool downIsDown;
	bool leftIsDown;
	bool rightIsDown;

	PlayerInputListener(int entityId, KeyboardKey upKey, KeyboardKey downKey, KeyboardKey leftKey, KeyboardKey rightKey)
		: upKey(upKey)
		, downKey(downKey)
		, leftKey(leftKey)
		, rightKey(rightKey)
		, upIsDown(false)
		, downIsDown(false)
		, leftIsDown(false)
		, rightIsDown(false)
	{
		entity = entityId;
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
	KeyboardKey lastPressed;

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

	// key = component id, value = vector<component>
	std::unordered_map<int, void*> componentTable;

	SpriteRendererSystem& spriteRendererSystem;
	RigidBodySystem& rigidBodySystem;
	ForceSystem& forceSystem;
	SpeedLimiterSystem& speedLimiterSystem;
	InputSystem& inputSystem;

	int ComponentIdOffset(int componentId);

public:
	Scene(SpriteRendererSystem& spriteRendererSystem,
				RigidBodySystem& rigidBodySystem,
				ForceSystem& forceSystem,
				SpeedLimiterSystem& speedLimiterSystem,
				InputSystem& inputSystem);

	int CreateEntity();
	void Update();

	template<typename T, typename... Args>
	bool AddComponent(int entityId, Args... args);

	template<typename T>
	bool RemoveComponent(int entityId);

	template<typename T>
	T& GetComponent(int entityId);

	template<typename T>
	bool HasComponent(int entityId);
};

template<typename T, typename... Args>
bool Scene::AddComponent(int entityId, Args... args)
{
	bool successful = !HasComponent<T>(entityId);

	if (successful)
	{
		entities[entityId].componentMask |= T::ID;
		std::vector<T>* componentList;
		if (componentTable.find(T::ID) != componentTable.end())
			componentList = static_cast<std::vector<T>*>(componentTable[T::ID]);
		else
		{
			componentList = new std::vector<T>;
			componentTable[T::ID] = static_cast<void*>(componentList);
		}
		componentList->emplace_back(entityId, args...);
		components[entityId * Component::COMPONENT_COUNT + ComponentIdOffset(T::ID)] = static_cast<int>(componentList->size()) - 1;
	}

	return successful;
}

template<typename T>
bool Scene::RemoveComponent(int entityId)
{
	bool successful = HasComponent<T>(entityId);

	if (successful)
	{
		int index = components[entityId * Component::COMPONENT_COUNT + ComponentIdOffset(T::ID)];
		std::vector<T>* componentList;
		componentList = static_cast<std::vector<T>*>(componentTable[T::ID]);

		// swap and pop approach to keep vectors tightly packed
		if (index < componentList->size())
		{
			T toRemove = (*componentList)[index];
			T back = componentList->back();

			(*componentList)[componentList->size() - 1] = toRemove;
			(*componentList)[index] = back;

			components[back.entity * Component::COMPONENT_COUNT + ComponentIdOffset(T::ID)] = index;
		}

		components[entityId * Component::COMPONENT_COUNT + ComponentIdOffset(T::ID)] = -1;
		componentList->pop_back();

		entities[entityId].componentMask &= ~T::ID;
	}

	return successful;
}

template<typename T>
T& Scene::GetComponent(int entityId)
{
	int index = components[entityId * Component::COMPONENT_COUNT + ComponentIdOffset(T::ID)];

	std::vector<T>* componentList;
	componentList = static_cast<std::vector<T>*>(componentTable[T::ID]);

	return (*componentList)[index];
}

template<typename T>
bool Scene::HasComponent(int entityId)
{
	return  (entities[entityId].componentMask & T::ID) != 0;
}

#endif
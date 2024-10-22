#pragma once
#include "Entity.h"
#include "SpriteManager.h"
#include "Sprite.h"

#include <vector>
#include <unordered_map>

class Scene;

class SpriteManagerSystem
{
private:
	std::unordered_map<EntityTag, SpriteAtlas*> spriteAtlases;

	void UpdateState(Scene* scene, SpriteManager& spriteManager);
	void UpdateOrientation(Scene* scene, SpriteManager& spriteManager);

public:
	SpriteManagerSystem();
	~SpriteManagerSystem();
	void Update(Scene* scene, std::vector<SpriteManager>& spriteManagers);
};
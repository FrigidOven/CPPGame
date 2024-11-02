#pragma once

#include "Scene.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "SpriteAtlas.h"
#include "Tags.h"

#include <vector>
#include <unordered_map>


class SpriteManagerSystem
{
private:

	PlayerSpriteAtlas playerSpriteAtlas;

	std::unordered_map<EntityType, SpriteAtlas*> spriteAtlases
	{
		{ EntityType::Player, &playerSpriteAtlas}
	};

public:
	void Update(Scene& scene, std::vector<SpriteManager>& spriteManagers);
};
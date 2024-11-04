#pragma once

#include "Scene.h"
#include "SpriteAtlas.h"

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
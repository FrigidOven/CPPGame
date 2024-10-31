#pragma once

#include "Scene.h"
#include "SpriteManager.h"
#include "Sprite.h"

#include <vector>
#include <unordered_map>


class SpriteManagerSystem
{
private:

	PlayerSpriteAtlas playerSpriteAtlas;

	std::unordered_map<EntityTag, SpriteAtlas*> spriteAtlases
	{
		{ EntityTag::Player, &playerSpriteAtlas}
	};

	void UpdateState(Scene& scene, SpriteManager& spriteManager);

public:
	void Update(Scene& scene, std::vector<SpriteManager>& spriteManagers);
};
#pragma once

#include "Scene.h"
#include "Sprite.h"

#include <vector>

class SpriteRendererSystem
{
private:
	void UpdateSprite(Sprite& sprite, float deltaTime);

public:
	void Update(Scene& scene, std::array<std::vector<Sprite>, 16>& spriteLayers, float deltaTime);
};
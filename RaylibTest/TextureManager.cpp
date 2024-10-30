#include "TextureManager.h"

TextureManager::TextureManager()
{
	background = LoadTexture("Textures/Background.png");
	player = LoadTexture("Textures/GolemSprite.png");
}

const Texture2D* TextureManager::GetBackgroundTexture()
{
	return &background;
}

const Texture2D* TextureManager::GetPlayerTexture()
{
	return &player;
}
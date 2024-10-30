#pragma once

#include <raylib.h>

class TextureManager
{
private:
	Texture2D background;
	Texture2D player;

public:
	TextureManager();

	const Texture2D* GetBackgroundTexture();
	const Texture2D* GetPlayerTexture();
};
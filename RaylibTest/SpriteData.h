#pragma once

#include <raylib.h>

struct Frame
{
	const Texture2D* source;
	Rectangle sourceRect;
	Vector2 destWidthHeight;
	Vector2 offset;
	float durration;
	Color tint;

	Frame(const Texture2D* source, Rectangle sourceRect, Vector2	destWidthHeight, Vector2 offset, float durration, Color tint)
		: source(source)
		, sourceRect(sourceRect)
		, destWidthHeight(destWidthHeight)
		, offset(offset)
		, durration(durration)
		, tint(tint)
	{
	}
};
#pragma once

enum class EntityTag
{
	Untagged,
	Player
};

struct Entity
{
	int id; // Unique ID for the entity
	EntityTag tag; // What the entity is
	int componentMask; // Bit mask for components

	Entity(int id, EntityTag tag, int componentMask)
		: id(id)
		, tag(tag)
		, componentMask(componentMask)
	{
	}
};
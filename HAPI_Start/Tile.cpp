#include "Tile.h"

bool Tile::TakeDamage(const Entity& argEntity)
{
	return true;
}

Tile::Tile(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	:	Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller>()))
{
}

void Tile::Update()
{
}

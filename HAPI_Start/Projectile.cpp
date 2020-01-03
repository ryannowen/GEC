#include "Projectile.h"
#include "World.h"

void Projectile::OnAnimFinished()
{
	SetActive(false);
}

void Projectile::OnDisable()
{
	WORLD.SpawnExplosion(currentPosition);
}

Projectile::Projectile(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller>()))
{
}

void Projectile::Update()
{
	ApplyPhysics();
}


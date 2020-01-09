#include "Projectile.h"
#include "World.h"

void Projectile::OnAnimFinished()
{
	SetActive(false);
}

void Projectile::OnDisable()
{
	/// Spawns explosion

	velocity = Vector2<float>(0, 0);
	spriteAnimData.currentPlaybackTime = 0;
	spriteAnimData.currentSpriteCells = Vector2<unsigned int>(0, 0);
	WORLD.SpawnEntity(ESpawnableEntities::eMagicExplosion, currentPosition, Vector2<float>(50,50));
}

Projectile::Projectile(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller>()))
{
	passable = true;
}

void Projectile::Update()
{
	ApplyPhysics(Vector2<float>(1, 1));
}


#include "Projectile_Fireball.h"

#include "World.h"

void Projectile_Fireball::OnDisable()
{
	/// Spawns explosion and flame blocker

	velocity = Vector2<float>(0, 0);
	spriteAnimData.currentPlaybackTime = 0;
	spriteAnimData.currentSpriteCells = Vector2<unsigned int>(0, 0);
	WORLD.SpawnEntity(ESpawnableEntities::eFireExplosion, currentPosition, Vector2<float>(50, 50));
	WORLD.SpawnEntity(ESpawnableEntities::eFlame, currentPosition, Vector2<float>(10, 0), entityController->GetSide(), Vector2<float>(0, 0), 0, 0, damage);
}

Projectile_Fireball::Projectile_Fireball(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Projectile(argSpritePath, argAnimData, argCollisionBounds)
{
}

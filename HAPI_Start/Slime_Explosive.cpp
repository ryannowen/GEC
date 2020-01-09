#include "Slime_Explosive.h"

#include "World.h"
#include "Audio.h"

void Slime_Explosive::OnDeath()
{
	WORLD.IncreaseDefeatedEnemies();
	WORLD.AddScore(20);

	AUDIO.PlaySound(deathSound);
}

void Slime_Explosive::OnAnimFinished()
{
	if (isAttacking)
	{
		SetActive(false);
		OnDeath();
	}
}

Slime_Explosive::Slime_Explosive(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Slime(argSpritePath, argAnimData, argCollisionBounds)

{
}


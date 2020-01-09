#include "Slime_Slimeling.h"

#include "Slime_Boss.h"
#include "Audio.h"

void Slime_Slimeling::OnDeath()
{
	/// If slime boss reference is correct then trigger it's death
	if (slimeBoss != nullptr)
	{
		slimeBoss->SlimelingDeath();
		AUDIO.PlaySound(deathSound);
	}
	else
		std::cerr << "ERROR: Trying to increase slime bosses death count but pointer is null, entityID=" << entityID << std::endl;
}

Slime_Slimeling::Slime_Slimeling(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Slime_Explosive(argSpritePath, argAnimData, argCollisionBounds)

{
}

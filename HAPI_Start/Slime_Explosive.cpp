#include "Slime_Explosive.h"

void Slime_Explosive::OnAnimFinished()
{
	if (isAttacking)
	{
		SetActive(false);
	}
}

Slime_Explosive::Slime_Explosive(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Slime(argSpritePath, argAnimData, argCollisionBounds)

{
}


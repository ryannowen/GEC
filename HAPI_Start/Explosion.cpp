#include "Explosion.h"

void Explosion::OnAnimFinished()
{
	SetActive(false);
}

Explosion::Explosion(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle argCollision)
	: Entity(argSpritePath, argAnimData, argCollision, std::shared_ptr<Controller>(std::make_shared<Controller>()))
{
	passable = true;
}

void Explosion::Update()
{
}

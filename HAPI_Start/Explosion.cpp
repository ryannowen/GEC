#include "Explosion.h"

void Explosion::OnAnimFinished()
{
	std::cout << "Anim finished "<< std::endl;
	SetActive(false);
}

Explosion::Explosion(const std::string& argSpritePath, const AnimationData& argAnimData)
	: Entity(argSpritePath, argAnimData, Rectangle(0,0,0,0), std::shared_ptr<Controller>(std::make_shared<Controller>()))
{
}

void Explosion::Update()
{
}

void Explosion::Collided(Entity& argEntity)
{
}

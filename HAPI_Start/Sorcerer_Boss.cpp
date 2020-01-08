#include "Sorcerer_Boss.h"

#include "Controller_Sorcerer_Boss.h"

bool Sorcerer_Boss::Attack(const Vector2<float> argDirection)
{
	return false;
}

void Sorcerer_Boss::OnDeath()
{
}

void Sorcerer_Boss::OnDisable()
{
}

Sorcerer_Boss::Sorcerer_Boss(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	:	Sorcerer(argSpritePath, argAnimData, argCollisionBounds, std::static_pointer_cast<Controller>(std::make_shared<Controller_Sorcerer_Boss>()))
{
}

void Sorcerer_Boss::Update()
{
}

void Sorcerer_Boss::ResetEntity()
{
}

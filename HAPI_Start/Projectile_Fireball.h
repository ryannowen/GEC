#pragma once
#include "Projectile.h"
class Projectile_Fireball : public Projectile
{
protected:
	virtual void OnDisable() override final;
public:
	Projectile_Fireball(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);
};


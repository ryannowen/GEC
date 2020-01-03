#pragma once
#include "Entity.h"
class Projectile : public Entity
{
protected:
	virtual void OnAnimFinished() override;
	virtual void OnDisable() override final;
public:
	Projectile(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);

	virtual void Update() override;
};


#pragma once
#include "Entity.h"
class Projectile : public Entity
{
protected:
	virtual void OnAnimFinished() override final;
	virtual void OnDisable() override;
public:
	Projectile(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);

	virtual void Update() override final;
};


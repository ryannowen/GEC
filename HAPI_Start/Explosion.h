#pragma once
#include "Entity.h"
class Explosion : public Entity
{
protected:
	virtual void OnAnimFinished() override final;

public:
	Explosion(const std::string& argSpritePath, const AnimationData& argAnimData);
	virtual void Update() override final;

	virtual void Collided(Entity& argEntity) override final;
};


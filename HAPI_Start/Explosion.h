#pragma once
#include "Entity.h"
class Explosion : public Entity
{
protected:
	virtual void OnAnimFinished() override final;

public:
	Explosion(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle argCollision = Rectangle(0, 0, 0, 0));
	virtual void Update() override final;
};


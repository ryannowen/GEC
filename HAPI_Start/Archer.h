#pragma once
#include "Entity.h"
class Archer : public Entity
{
protected:
	virtual void ApplyPhysics() override final;

public:
	Archer(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds = Rectangle(32, 0, 32, 0));

	virtual void Update() override final;
};


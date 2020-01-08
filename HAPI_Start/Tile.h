#pragma once
#include "Entity.h"
class Tile : public Entity
{
protected:
	virtual bool TakeDamage(const Entity& argEntity) override final;

public:
	Tile(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds = Rectangle(32, 0, 32, 0));

	virtual void Update() override;
};


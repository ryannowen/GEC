#pragma once
#include "Entity.h"
class TriggerBox : public Entity
{
protected:
	virtual bool TakeDamage(const Entity& argEntity) override final;

public:
	TriggerBox(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds = Rectangle(32, 0, 32, 0));

	virtual void Update() override;
	virtual void Collided(Entity& argEntity) override final;

};


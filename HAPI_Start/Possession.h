#pragma once
#include "Entity.h"
class Possession : public Entity
{
public:
	Possession();

	virtual void Update() override final;
	virtual void Collided(Entity& argEntity) override final;
};


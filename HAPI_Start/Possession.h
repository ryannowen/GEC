#pragma once
#include "Entity.h"
class Possession : public Entity
{
public:
	Possession();

	// Updates entity
	virtual void Update() override final;

	// When entity collides with another
	virtual void Collided(Entity& argEntity) override final;
};


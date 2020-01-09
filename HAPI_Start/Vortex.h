#pragma once
#include "Entity.h"
class Vortex : public Entity
{
private:
	std::string teleportSound{ "Data//Sounds//Teleport.wav" };

protected:
	// Takes damage to health
	virtual bool TakeDamage(const Entity& argEntity) override final;

public:
	Vortex(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);

	// Updates entity
	virtual void Update() override;
	// When entity collides with another
	virtual void Collided(Entity& argEntity) override final;

};


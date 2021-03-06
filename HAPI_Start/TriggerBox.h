#pragma once
#include "Entity.h"
class Vortex : public Entity
{
private:
	std::string teleportSound{ "Data//Sounds//Teleport.wav" };
protected:
	virtual bool TakeDamage(const Entity& argEntity) override final;

public:
	Vortex(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);

	virtual void Update() override;
	virtual void Collided(Entity& argEntity) override final;

};


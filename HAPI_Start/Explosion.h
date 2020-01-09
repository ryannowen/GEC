#pragma once
#include "Entity.h"
class Explosion : public Entity
{
private:
	std::string sound{ "Data//Sounds//Explosion.wav" };

protected:
	// When entity finishes the current animation
	virtual void OnAnimFinished() override final;
	// When entity is enabled
	virtual void OnEnable() override final;

public:
	Explosion(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle argCollision = Rectangle(0, 0, 0, 0));
	// Updates entity
	virtual void Update() override final;
};


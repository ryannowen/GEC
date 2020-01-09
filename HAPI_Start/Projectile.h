#pragma once
#include "Entity.h"
class Projectile : public Entity
{
protected:
	// When entity finishes the current animation
	virtual void OnAnimFinished() override final;
	// When entity is disabled
	virtual void OnDisable() override;

public:
	Projectile(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);

	// Updates entity
	virtual void Update() override final;
};


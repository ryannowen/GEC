#pragma once
#include "Slime.h"
class Slime_Explosive : public Slime
{
protected:
	// When entity takes enough damage to die
	virtual void OnDeath() override;
	// When entity finishes the current animation
	virtual void OnAnimFinished() override final;

public:
	Slime_Explosive(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);

};


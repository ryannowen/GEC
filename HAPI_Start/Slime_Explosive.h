#pragma once
#include "Slime.h"
class Slime_Explosive : public Slime
{
protected:
	virtual void OnAnimFinished() override final;

public:
	Slime_Explosive(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds = Rectangle(32, 0, 32, 0));

};


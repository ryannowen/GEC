#pragma once
#include "Slime_Explosive.h"
class Slime_Slimeling : public Slime_Explosive
{
private:
	friend class Slime_Boss;
	Slime_Boss* slimeBoss{ nullptr };

protected:
	// When entity takes enough damage to die
	virtual void OnDeath() override final;

public:
	Slime_Slimeling(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);
};


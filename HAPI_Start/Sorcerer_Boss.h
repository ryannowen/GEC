#pragma once
#include "Sorcerer.h"

#include "Controller_Sorcerer_Boss.h"

class Sorcerer_Boss : public Sorcerer
{
private:
	friend class Controller_Sorcerer_Boss;

	// Entity Attack returns true if successful in attack
	virtual bool Attack(const Vector2<float> argDirection) override final;

protected:
	// When entity takes enough damage to die
	virtual void OnDeath() override final;

public:
	Sorcerer_Boss(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);

	// Updates entity
	virtual void Update() override final;
};


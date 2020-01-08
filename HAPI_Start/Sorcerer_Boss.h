#pragma once
#include "Sorcerer.h"
class Sorcerer_Boss : public Sorcerer
{
private:
	friend class Controller_Sorcerer_Boss;

	virtual bool Attack(const Vector2<float> argDirection);

protected:
	virtual void OnDeath() override final;
	virtual void OnDisable() override final;


public:
	Sorcerer_Boss(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);
	virtual void Update() override final;
	virtual void ResetEntity() override final;

};


#pragma once
#include "Entity.h"

#include "Controller_Slime.h"

class Slime : public Entity
{
private:
	

protected:
	virtual void OnAnimFinished() override;

	virtual void ApplyPhysics() override final;

public:
	Slime(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds = Rectangle(32, 0, 32, 0));
	virtual void Update() override final;
	
	virtual void Collided(Entity& argEntity) override final;


	bool isAttacking{ false };
	bool canAttack{ true };
	bool isCharging{ false };

	float reChargeDelay{ 0 };
	const float reChargeTime{ 4 };
};


#pragma once
#include "Entity.h"
class Archer : public Entity
{
private:
	friend class Controller_Archer;

	int attackDamage{ 0 };

	bool isAttacking{ false };
	bool canAttack{ true };
	bool isCharging{ false };

	float reChargeDelay{ 0 };
	const float reChargeTime{ 4 };

	bool Attack(const Vector2<float> argDirection);
protected:
	virtual void OnDeath() override final;
	virtual void OnAnimFinished() override final;
	virtual void OnDisable() override final;

public:
	Archer(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds = Rectangle(32, 0, 32, 0));

	virtual void Update() override final;
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage) override final;

	virtual void ResetEntity() override final;

};


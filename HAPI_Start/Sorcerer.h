#pragma once
#include "Entity.h"

#include "Controller_Sorcerer.h"

class Sorcerer : public Entity
{
private:
	friend class Controller_Sorcerer;

	virtual bool Attack(const Vector2<float> argDirection);

protected:
	int attackDamage{ 0 };

	bool isAttacking{ false };
	bool canAttack{ true };
	bool isCharging{ false };

	float reChargeDelay{ 0 };
	const float reChargeTime{ 3 };

	virtual void OnDeath() override;
	virtual void OnAnimFinished() override final;
	virtual void OnDisable() override;

public:
	Sorcerer(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::shared_ptr<Controller> argController = std::shared_ptr<Controller>(std::make_shared<Controller_Sorcerer>()));
	virtual void Update() override;
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage) override final;

	virtual void ResetEntity() override;

};


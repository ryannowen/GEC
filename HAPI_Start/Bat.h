#pragma once
#include "Entity.h"
class Bat : public Entity
{
private:
	friend class Controller_Bat;

	void Attack();
protected:
	int attackDamage{ 0 };

	bool canAttack{ true };
	bool isCharging{ false };

	float reChargeDelay{ 0 };
	const float reChargeTime{ 2 };

	virtual void OnDeath() override final;
	virtual void OnDisable() override final;

public:
	Bat(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);
	virtual void Update() override final;
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage) override final;

	virtual void AfterCollided(Entity& argEntity) override final;


	virtual void ResetEntity() override final;
};


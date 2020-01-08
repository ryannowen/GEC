#pragma once
#include "Entity.h"

#include "Controller_Slime.h"

class Slime : public Entity
{
private:
	friend class Controller_Slime;

	std::string attackSound{"Data//Sounds//Slime_Attack.wav"};
	std::string deathSound{"Data//Sounds//Slime_Death.wav"};

	void Attack();

protected:
	int attackDamage{ 0 };

	bool isAttacking{ false };
	bool canAttack{ true };
	bool isCharging{ false };

	float reChargeDelay{ 0 };
	const float reChargeTime{ 4 };

	virtual void OnDeath() override;
	virtual void OnAnimFinished() override;
	virtual void OnDisable() override final;

public:
	Slime(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);
	virtual void Update() override final;
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage) override final;

	virtual void AfterCollided(Entity& argEntity) override final;

	virtual void ResetEntity() override final;

};


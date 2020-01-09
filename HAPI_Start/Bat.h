#pragma once
#include "Entity.h"
class Bat : public Entity
{
private:
	friend class Controller_Bat;

	// Entity Attack
	void Attack();

protected:
	int attackDamage{ 0 };

	bool canAttack{ true };
	bool isCharging{ false };

	float spawnDelay{ 0 };
	const float spawnChargeTime{ 2 };

	std::string deathSound{ "Data//Sounds//Bat_Death.wav" };

	// When entity takes enough damage to die
	virtual void OnDeath() override final;
	// When entity is disabled
	virtual void OnDisable() override final;

public:
	Bat(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);
	// Updates entity
	virtual void Update() override final;
	// Init of entity, activating and setting the state
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage) override final;

	// After collision occurs
	virtual void AfterCollided(Entity& argEntity) override final;

	// Resets varaibles about entity
	virtual void ResetEntity() override final;
};


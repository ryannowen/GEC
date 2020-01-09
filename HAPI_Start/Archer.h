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

	float spawnDelay{ 0 };
	const float spawnChargeTime{ 4 };

	std::string attackSound{ "Data//Sounds//MagicAttack.wav" };
	std::string deathSound{ "Data//Sounds//Archer_Death.wav" };

	// Entity Attack returns true if successful in attack
	bool Attack(const Vector2<float> argDirection);
protected:
	// When entity takes enough damage to die
	virtual void OnDeath() override final;
	// When entity finishes the current animation
	virtual void OnAnimFinished() override final;
	// When entity is disabled
	virtual void OnDisable() override final;

public:
	Archer(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds = Rectangle(32, 0, 32, 0));

	// Updates entity
	virtual void Update() override final;
	// Init of entity, activating and setting the state
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage) override final;

	// Resets varaibles about entity
	virtual void ResetEntity() override final;
};


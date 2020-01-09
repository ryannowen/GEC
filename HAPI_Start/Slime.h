#pragma once
#include "Entity.h"

#include "Controller_Slime.h"

class Slime : public Entity
{
private:
	friend class Controller_Slime;

	// Entity Attack
	void Attack();

protected:
	std::string attackSound{ "Data//Sounds//Slime_Attack.wav" };
	std::string deathSound{ "Data//Sounds//Slime_Death.wav" };

	int attackDamage{ 0 };

	bool isAttacking{ false };
	bool canAttack{ true };
	bool isCharging{ false };

	float spawnDelay{ 0 };
	const float spawnChargeTime{ 4 };

	// When entity takes enough damage to die
	virtual void OnDeath() override;
	// When entity finishes the current animation
	virtual void OnAnimFinished() override;
	// When entity is disabled
	virtual void OnDisable() override final;

public:
	Slime(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);
	// Updates entity
	virtual void Update() override final;
	// Init of entity, activating and setting the state
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage) override final;
	
	// After collision occurs
	virtual void AfterCollided(Entity& argEntity) override final;

	// Resets varaibles about entity
	virtual void ResetEntity() override final;
};


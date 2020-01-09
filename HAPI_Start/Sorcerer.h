#pragma once
#include "Entity.h"

#include "Controller_Sorcerer.h"

class Sorcerer : public Entity
{
private:
	friend class Controller_Sorcerer;

	// Entity Attack returns true if successful in attack
	virtual bool Attack(const Vector2<float> argDirection);

protected:
	int attackDamage{ 0 };
	std::string attackSound{ "Data//Sounds//MagicAttack.wav" };
	std::string deathSound{ "Data//Sounds//Sorcerer_Death.wav" };


	bool isAttacking{ false };
	bool canAttack{ true };
	bool isCharging{ false };

	float spawnDelay{ 0 };
	const float spawnChargeTime{ 3 };

	// When entity takes enough damage to die
	virtual void OnDeath() override;
	// When entity finishes the current animation
	virtual void OnAnimFinished() override final;
	// When entity is disabled
	virtual void OnDisable() override final;

public:
	Sorcerer(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::shared_ptr<Controller>& argController);
	// Updates entity
	virtual void Update() override;
	// Init of entity, activating and setting the state
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage) override final;

	// Resets varaibles about entity
	virtual void ResetEntity() override final;

};


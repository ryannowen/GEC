#pragma once
#include "Entity.h"

#include "Slime_Slimeling.h"
#include "Controller_Slime_Boss.h"

class Slime_Boss : public Entity
{
private:
	friend class Slime_Slimeling;
	friend class Controller_Slime_Boss;

	std::string attackSound{ "Data//Sounds//Slime_Attack.wav" };
	std::string deathSound{ "Data//Sounds//Slime_Death.wav" };

	int maxHealth{ 0 };
	int attackDamage{ 0 };

	bool isCharging{ false };
	int spawnedSlimelings{ 0 };

	float spawnDelay{ 0 };
	const float spawnChargeTime{ 3 };

	// When slimeling dies, it calls this to hurt slime boss
	void SlimelingDeath();
	
	// Entity Attack returns true if successful in attack
	bool Attack();

protected:
	// When entity takes enough damage to die
	virtual void OnDeath() override final;

	// When entity is disabled
	virtual void OnDisable() override final;

	// Takes damage to health
	virtual bool TakeDamage(const Entity& argEntity) override final;
public:
	Slime_Boss(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds);

	// Updates entity
	virtual void Update() override final;

	// Init of entity, activating and setting the state
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage) override final;

	// Resets varaibles about entity
	virtual void ResetEntity() override final;

};


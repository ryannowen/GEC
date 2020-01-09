#pragma once
#include "Entity.h"


class Player : public Entity
{
private:
	friend class Controller_Player;
	friend class UI_Window_HUD;
	friend class UI_Button_Reward;

	int maxHealth{ 10 };
	int projectileDamage{ 1 };

	std::string attackSound{ "Data//Sounds//MagicAttack.wav" };

	float attackDelay{ 0 };
	float attackChargeTime{ 1 };
	bool canAttack{ true };
	bool isAttacking{ false };

	// Entity Attack returns true if successful in attack
	bool Attack();
protected:
	// When entity takes enough damage to die
	virtual void OnDeath() override final;
	// When entity finishes the current animation
	virtual void OnAnimFinished() override final;
	// Applies gravity and movement physics to entity
	virtual void ApplyPhysics(const Vector2<float> argDirection) override final;

public:
	Player(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::vector<int>& argKeyboardMovementKeys, const std::vector<int>& argControllerMovementKeys);
	// Updates entity
	virtual void Update() override;
	// Init of entity, activating and setting the state
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage) override final;

	// Resets varaibles about entity
	virtual void ResetEntity() override final;
};


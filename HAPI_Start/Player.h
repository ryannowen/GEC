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

	bool Attack();
protected:
	virtual void OnDeath() override final;
	virtual void OnAnimFinished() override final;
	virtual void ApplyPhysics(const Vector2<float> argDirection) override final;

	Vector2<int> previousOffset{ -5, 1 }; // TODO Remove
	int spawnedAmount{ 0 }; // TODO Remove
public:
	Vector2<unsigned int> cellLoc{ 4, 3 }; // TODO Remove

	Player(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::vector<int>& argKeyboardMovementKeys, const std::vector<int>& argControllerMovementKeys);
	virtual void Update() override;
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage) override final;

	virtual void ResetEntity() override final;
};


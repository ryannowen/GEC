#pragma once
#include "Entity.h"


class Player : public Entity
{
protected:
	static unsigned int numOfPlayers;
	unsigned int playerID{ 0 };

	float attackDelay{ 0 };
	float attackChargeTime{ 2 };
	bool attackReady{ true };

	virtual void OnAnimFinished() override final;
	virtual void ApplyPhysics() override final;


	Vector2<int> previousOffset{ -5, 1 }; // TODO Remove
	int spawnedAmount{ 0 };
public:
	Vector2<unsigned int> cellLoc{ 0, 0 }; // TODO Remove

	Player(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::vector<int>& argKeyboardMovementKeys, const std::vector<int>& argControllerMovementKeys);
	void Update() override;

	bool CanAttack() const { return (attackReady && GetActive()); };
	bool Attack();

};


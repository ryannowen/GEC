#pragma once
#include "Entity.h"

#include "World.h"

class Player_Opposing : public Entity
{
private:
	friend class Controller_OpposingPlayer;


	void PlaceEntity();
	void PossessEntity();
	void ChangePlacementEntity();

protected:
	virtual void ApplyPhysics(const Vector2<float> argDirection) override final;

public:
	ESpawnableEntities currentPlacement{ ESpawnableEntities::eSlime }; // TODO move to private

	Player_Opposing(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::vector<int>& argKeyboardMovementKeys, const std::vector<int>& argControllerMovementKeys);

	virtual void Update() override final;
	virtual void Collided(Entity& argEntity) override final;

};


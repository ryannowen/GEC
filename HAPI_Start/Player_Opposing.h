#pragma once
#include "Entity.h"

#include "World.h"

class Player_Opposing : public Entity
{
private:
	friend class Controller_OpposingPlayer;

	bool isPossessing{ false };
	Entity* possessingEntity{ nullptr };

	bool canAction{ true };
	const float actionDelayTime{ 1.0f };
	float actionDelay{ 0 };

	std::string possessionSoundPath{ "Data//Sounds//Possession.wav" };

	// Places entity into the world
	void PlaceEntity();
	// Places possession into the world
	void PossessEntity();
	// Switches between placement entities
	void ChangePlacementEntity();

	ESpawnableEntities currentPlacement{ ESpawnableEntities::eSlime };

protected:
	// Applies gravity and movement physics to entity
	virtual void ApplyPhysics(const Vector2<float> argDirection) override final;

public:
	Player_Opposing(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::vector<int>& argKeyboardMovementKeys, const std::vector<int>& argControllerMovementKeys);

	// Updates entity
	virtual void Update() override final;
	// When entity collides with another
	virtual void Collided(Entity& argEntity) override final;

	// Stops possessing if possessing any entity
	void StopPossessing();
	// Begins possessing entity
	void BeginPossessing(Entity& argPossessing);

	// Returns current placement
	ESpawnableEntities GetCurrentPlacement() const { return currentPlacement; };
};


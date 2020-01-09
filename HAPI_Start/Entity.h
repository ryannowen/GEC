#pragma once

#include <iostream>
#include <vector>

/// My Headers
#include "Vector2.h"
#include "Controller.h"
#include "Rectangle.h"

class Renderer;

struct AnimationData
{
	AnimationData(const Vector2<unsigned int> argSpriteSheetSize, const std::vector<float>& argAnimPlaybackSpeeds, const std::vector<unsigned int>& argAnimNumOfCells, const std::vector<bool>& argAnimShouldLoop, const Vector2<unsigned int> argCurrentSpriteCells = Vector2<unsigned int>(0, 0), const bool argHasAnimation = false)
		: spriteSheetSize(argSpriteSheetSize), animPlaybackSpeeds(argAnimPlaybackSpeeds), animNumOfCells(argAnimNumOfCells), animShouldLoop(argAnimShouldLoop), currentSpriteCells(argCurrentSpriteCells), hasAnimation(argHasAnimation)
	{
	}

	bool hasAnimation{ false };
	double currentPlaybackTime{ 0 };
	Vector2<unsigned int> currentSpriteCells{ 0, 0 };

	// Gets current animation cells
	float GetCurrentPlaybackSpeed() 
	{ 
		if(currentSpriteCells.y < animPlaybackSpeeds.size())
			return animPlaybackSpeeds[currentSpriteCells.y]; 

		return 0.0f;
	};

	// Gets current animation number of cells
	unsigned int GetAnimNumOfCells()
	{
		if (currentSpriteCells.y < animNumOfCells.size())
			return animNumOfCells[currentSpriteCells.y];

		return 1;
	}

	// Gets current animation shouldLoop
	bool GetAnimShouldLoop()
	{
		if (currentSpriteCells.y < animShouldLoop.size())
			return animShouldLoop[currentSpriteCells.y];

		return false;
	}

	// Gets sprite sheet size
	Vector2<unsigned int> GetSpriteSheetSize() { return spriteSheetSize; };

private:
	Vector2<unsigned int> spriteSheetSize{ 0, 0 };

	std::vector<float> animPlaybackSpeeds;
	std::vector<unsigned int> animNumOfCells;
	std::vector<bool> animShouldLoop;
};

class Entity
{
private:
	friend class Possession;
	friend class Player_Opposing;

	static size_t numOfEntities;

protected:
	static unsigned short numOfPlayers;
	unsigned short playerID{ 0 };
	size_t entityID{ 0 };

	bool active{ false };

	std::shared_ptr<Controller> entityController{ nullptr };
	bool isPossessed{ false };
	bool isPossessable{ false };

	std::string spritePath;

	Rectangle collisionBounds;
	bool hasCollision{ true };
	bool passable{ false };

	int health{ 0 };
	int damage{ 0 };

	Vector2<float> oldPosition{ 0.0f, 0.0f };
	Vector2<float> currentPosition{ 0.0f, 0.0f };

	Vector2<float> acceleration{ 0.0f, 0.0f };
	Vector2<float> velocity{ 0.0f, 0.0f };

	Vector2<float> speed{ 200, 7500 };
	float maxSpeed{ 400 };
	float drag{ 150 };
	float gravity{ 500 };
	bool hasGravity{ false };
	bool isGrounded{ false };

	// When entity takes enough damage to die
	virtual void OnDeath();
	// When entity finishes the current animation
	virtual void OnAnimFinished();
	// When entity is disabled
	virtual void OnDisable();
	// When entity is enabled
	virtual void OnEnable();


	// Moves entity by position amount
	void Translate(Vector2<float>& argPosition);

	virtual void ApplyPhysics(const Vector2<float> argDirection);
	// Returns true if entity is alive
	virtual bool TakeDamage(const Entity& argEntity);

public:
	AnimationData spriteAnimData;

	Entity(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::shared_ptr<Controller>& argController);
	// Updates entity
	virtual void Update() = 0;

	// Init of entity, activating and setting the state
	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage);

	// Swaps controller input and playerIDs
	void SwapControllerInput(Entity& argEntity);

	bool CheckCollision(const Entity& argEntity) const;
	// After collision occurs
	virtual void Collided(Entity& argEntity);
	// After collision occurs
	virtual void AfterCollided(Entity& argEntity);

	// Creates sprite for entity
	bool CreateSprite(bool argHasAlpha, const Vector2<unsigned int> argNumOfSpriteCells);
	// Draws entity to screen
	void Draw(const float argInterp, const float argCameraOffset);

	// Resets varaibles about entity
	virtual void ResetEntity();

	// Sets position of entity
	void SetPosition(const Vector2<float> argNewPosition) { oldPosition = argNewPosition; currentPosition = argNewPosition; };

	// Adds velocity to entity
	void AddVelocity(Vector2<float> argVelocity);
	// Adds acceleration to entity
	void AddAcceleration(Vector2<float> argAcceleration);
	
	// Set velocity
	void SetVelocity(Vector2<float> argVelocity);
	// Sets acceleration
	void SetAcceleration(Vector2<float> argAcceleration);
	// Sets sprite path
	void SetSpritePath(const std::string& argSpritePath) { spritePath = argSpritePath; };
	// Sets active state of entity
	void SetActive(const bool argActive);
	// Sets isGround
	void SetGrounded(const bool argGrounded) { isGrounded = argGrounded; };

	// Returns current position
	Vector2<float> GetPosition() const { return currentPosition; };
	// Returns Sprite path
	std::string GetSpritePath() const { return spritePath; };
	// Returns side of entity controller
	ESide GetSide() const { return entityController->GetSide(); };
	// Returns active state
	bool GetActive() const { return active; };
	// Returns if passable
	bool GetPassable() const { return passable; };

	// Checks entity ID's
	inline bool operator==(const Entity& argEntity)
	{
		return (entityID == argEntity.entityID);
	}
};



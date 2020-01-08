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

	float GetCurrentPlaybackSpeed() 
	{ 
		if(currentSpriteCells.y < animPlaybackSpeeds.size())
			return animPlaybackSpeeds[currentSpriteCells.y]; 

		return 0.0f;
	};

	unsigned int GetAnimNumOfCells()
	{
		if (currentSpriteCells.y < animNumOfCells.size())
			return animNumOfCells[currentSpriteCells.y];

		return 1;
	}

	bool GetAnimShouldLoop()
	{
		if (currentSpriteCells.y < animShouldLoop.size())
			return animShouldLoop[currentSpriteCells.y];

		return false;
	}

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

	static size_t numOfEntities;

protected:
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


	Vector2<float> acceleration{ 0.0f, 0.0f };
	Vector2<float> velocity{ 0.0f, 0.0f };

	Vector2<float> speed{ 200, 7500 };
	float maxSpeed{ 400 };
	float drag{ 150 };
	float gravity{ 500 };
	bool hasGravity{ false };
	bool isGrounded{ false };

	virtual void OnDeath();
	virtual void OnAnimFinished();
	virtual void OnDisable();
	virtual void OnEnable();


	// Moves entity by position amount
	void Translate(Vector2<float>& argPosition);

	virtual void ApplyPhysics(const Vector2<float> argDirection);

	// Returns true if entity is alive
	virtual bool TakeDamage(const Entity& argEntity);

public:
	Vector2<float> oldPosition{ 0.0f, 0.0f }; // TODO MOVE TO PROTECTED
	Vector2<float> currentPosition{ 0.0f, 0.0f }; // TODO MOVE TO PROTECTED
	AnimationData spriteAnimData; //TODO MOVE TO PROTECTED

	Entity(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::shared_ptr<Controller>& argController);
	virtual void Update() = 0;

	virtual void Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage);

	void SwapControllerInput(std::shared_ptr<Entity> argEntity);

	bool CheckCollision(const Entity& argEntity) const;
	virtual void Collided(Entity& argEntity);
	virtual void AfterCollided(Entity& argEntity);

	bool CreateSprite(bool argHasAlpha, const Vector2<unsigned int> argNumOfSpriteCells);
	void Draw(const float argInterp, const float argCameraOffset);

	virtual void ResetEntity();


	void AddVelocity(Vector2<float> argVelocity);
	void AddAcceleration(Vector2<float> argAcceleration);

	void SetVelocity(Vector2<float> argVelocity);
	void SetAcceleration(Vector2<float> argAcceleration);

	void SetSpritePath(const std::string& argSpritePath) { spritePath = argSpritePath; };
	void SetActive(const bool argActive);
	void SetGrounded(const bool argGrounded) { isGrounded = argGrounded; };

	std::string GetSpritePath() const { return spritePath; };
	ESide GetSide() const { return entityController->GetSide(); };
	bool GetActive() const { return active; };
	bool GetPassable() const { return passable; };

	inline bool operator==(const Entity& argEntity)
	{
		return (entityID == argEntity.entityID);
	}

};



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
	AnimationData(const std::vector<float>& argAnimPlaybackSpeeds, const std::vector<unsigned int>& argAnimNumOfCells, const std::vector<bool>& argAnimShouldLoop, const Vector2<unsigned int>& argCurrentSpriteCells = Vector2<unsigned int>(0, 0), const bool argHasAnimation = false)
		: animPlaybackSpeeds(argAnimPlaybackSpeeds), animNumOfCells(argAnimNumOfCells), animShouldLoop(argAnimShouldLoop), currentSpriteCells(argCurrentSpriteCells), hasAnimation(argHasAnimation)
	{}

	bool hasAnimation{ false };
	bool finishedOnce{ false };
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

private:
	std::vector<float> animPlaybackSpeeds;
	std::vector<unsigned int> animNumOfCells;
	std::vector<bool> animShouldLoop;
};

class Entity
{
private:
	bool active{ false };


protected:
	std::shared_ptr<Controller> entityController{ nullptr };

	std::string spritePath;

	Rectangle collisionBounds;

	int health{ 0 };
	int damage{ 0 };


	Vector2<float> acceleration{ 0.0f, 0.0f };
	Vector2<float> velocity{ 0.0f, 0.0f };

	Vector2<float> speed{ 200, 7500 };
	float maxSpeed{ 400 };
	float drag{ 150 };
	float gravity{ 500 };

	bool isGrounded{ false };

	virtual void OnAnimFinished();
	
	virtual void OnDisable();
	virtual void OnEnable();


	// Moves entity by position amount
	void Translate(Vector2<float>& argPosition);

	virtual void ApplyPhysics();

	// Returns true if entity is alive
	virtual bool TakeDamage(const Entity& argEntity);

public:
	Vector2<float> oldPosition{ 0.0f, 0.0f }; // TODO MOVE TO PROTECTED
	Vector2<float> currentPosition{ 0.0f, 0.0f }; // TODO MOVE TO PROTECTED
	AnimationData spriteAnimData; //TODO MOVE TO PROTECTED

	Entity(const std::string& argTexturePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::shared_ptr<Controller>& argController);
	virtual void Update() = 0;

	void Init(const Vector2<float>& argPosition, const Vector2<float>& argSpeed, const ESide argSide, const int argHealth, const int argDamage);

	void SwapController(std::shared_ptr<Entity>& argEntity);
	bool CheckCollision(const Entity& argEntity) const;
	virtual void Collided(Entity& argEntity);

	bool CreateSprite(bool argHasAlpha, const Vector2<int> argNumOfSpriteCells);
	void Draw(const float argInterp, const float argCameraOffset);



	void AddVelocity(Vector2<float> argVelocity);
	void AddAcceleration(Vector2<float> argAcceleration);

	void SetVelocity(Vector2<float> argVelocity);
	void SetAcceleration(Vector2<float> argAcceleration);

	void SetActive(const bool argActive);
	void SetDamage(const int argDamage) { damage = argDamage; };
	void SetGrounded(const bool argGrounded) { isGrounded = argGrounded; };

	ESide GetSide() const { return entityController->GetSide(); };
	bool GetActive() const { return active; };
};


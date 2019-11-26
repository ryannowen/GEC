#pragma once
#include "Entity.h"

#include "Controller.h"

class Player : public Entity
{
protected:
	Controller playerController;

	Vector2<float> acceleration{ 0.0f, 0.0f };
	Vector2<float> velocity{ 0.0f, 0.0f };

	Vector2<float> playerSpeed{ 1600.0f, 900.0f };
	float maxSpeed{ 0.45f };
	float drag{ 0.002f };

public:
	Player(Vector2<float> argPosition, std::string argTexturePath, std::vector<int>& argKeyboardMovementKeys, std::vector<int>& argControllerMovementKeys);
	void Update() override;

	void AddVelocity(Vector2<float> argVelocity);
	void AddAcceleration(Vector2<float> argAcceleration);

	void SetVelocity(Vector2<float> argVelocity);
	void SetAcceleration(Vector2<float> argAcceleration);
};


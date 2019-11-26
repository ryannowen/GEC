#include "Player.h"

#include "Time.h"

Player::Player(Vector2<float> argPosition, std::string argTexturePath, std::vector<int>& argKeyboardMovementKeys, std::vector<int>& argControllerMovementKeys)
	: Entity(argPosition, argTexturePath)
{
	playerController.SetKeyboardMovementKeys(argKeyboardMovementKeys);
	playerController.SetControllerMovementKeys(argControllerMovementKeys);
}

void Player::Update()
{
	Vector2<float> playerDir{ playerController.GetMovementDirection() };

	Translate((playerDir * playerSpeed) * TIME.GetTickTimeSeconds());

	if (HAPI.GetKeyboardData().scanCode['D'])
		currentSpriteCells.x++;
	else if (HAPI.GetKeyboardData().scanCode['A'])
		currentSpriteCells.x--;

	if (HAPI.GetKeyboardData().scanCode['W'])
		currentSpriteCells.y++;
	else if (HAPI.GetKeyboardData().scanCode['S'])
		currentSpriteCells.y--;

	/*acceleration += (playerDir * playerSpeed);

	velocity += acceleration;

	if (velocity.x > maxSpeed)
		velocity.x = maxSpeed;
	else if (velocity.x < -maxSpeed)
		velocity.x = -maxSpeed;

	if (velocity.y > maxSpeed)
		velocity.y = maxSpeed;
	else if (velocity.y < -maxSpeed)
		velocity.y = -maxSpeed;


	if (velocity.x != 0)
	{
		if (velocity.x > 0)
		{
			velocity.x -= drag;
			if (velocity.x < 0)
				velocity.x = 0;
		}
		else
		{
			velocity.x += drag;
			if (velocity.x > 0)
				velocity.x = 0;
		}
	}

	if (velocity.y != 0)
	{
		if (velocity.y > 0)
		{
			velocity.y -= drag;
			if (velocity.y < 0)
				velocity.y = 0;
		}
		else
		{
			velocity.y += drag;
			if (velocity.y > 0)
				velocity.y = 0;
		}
	}

	Translate(velocity * Time::GetDeltaTime());

	acceleration = Vector2<float>(0.0f, 0.0f);*/
}

void Player::AddVelocity(Vector2<float> argVelocity)
{
	velocity += argVelocity;
}

void Player::AddAcceleration(Vector2<float> argAcceleration)
{
	acceleration += argAcceleration;
}

void Player::SetVelocity(Vector2<float> argVelocity)
{
	velocity = argVelocity;
}

void Player::SetAcceleration(Vector2<float> argAcceleration)
{
	acceleration = argAcceleration;
}

#include "Slime.h"

#include "Time.h"
#include "World.h"

void Slime::OnAnimFinished()
{
	if (isAttacking)
	{
		isCharging = true;
		isAttacking = false;
		damage = 0;
	}
}

void Slime::ApplyPhysics()
{
	const std::shared_ptr<Entity> player{ WORLD.GetPlayer() };

	Vector2<float> dir{ player->currentPosition - currentPosition };

	dir.Normalise();

	
	velocity.y += gravity * TIME.GetTickTimeSeconds(); /// Applies Gravity
	

	acceleration += (dir * speed) * TIME.GetTickTimeSeconds();


	velocity += acceleration;

	if (velocity.x > maxSpeed)
		velocity.x = maxSpeed;
	else if (velocity.x < -maxSpeed)
		velocity.x = -maxSpeed;

	if (static_cast<int>(velocity.x) != 0)
	{
		if (velocity.x > 0)
		{
			velocity.x -= drag * TIME.GetTickTimeSeconds();
			if (velocity.x < 0)
				velocity.x = 0;
		}
		else
		{
			velocity.x += drag * TIME.GetTickTimeSeconds();
			if (velocity.x > 0)
				velocity.x = 0;
		}
	}



	Translate(velocity * TIME.GetTickTimeSeconds());

	acceleration = Vector2<float>(0.0f, 0.0f);

	isGrounded = false;
}

Slime::Slime(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller_Slime>()))
{
}

void Slime::Update()
{
	entityController->Update(*this, 0);
	spriteAnimData.currentSpriteCells.y = static_cast<int>(entityController->GetAction());

//	velocity.y += gravity * TIME.GetTickTimeSeconds();
	//Translate(velocity);

	if (isCharging)
	{
		reChargeDelay += TIME.GetTickTimeSeconds();

		if (reChargeDelay >= reChargeTime)
		{
			reChargeDelay = 0;
			isCharging = false;
			canAttack = true;
		}
	}
	else if (isAttacking)
		return;
	else if (entityController->GetAction() == EAction::eMoveLeft || entityController->GetAction() == EAction::eMoveRight)
		ApplyPhysics();
}


void Slime::Collided(Entity& argEntity)
{
	/// Applies damage
	TakeDamage(argEntity);

	/// This entity
	if (static_cast<int>(currentPosition.y) != static_cast<int>(oldPosition.y))
	{
		currentPosition.y = oldPosition.y;

		velocity = Vector2<float>(velocity.x, 0);
	}
	else if (static_cast<int>(currentPosition.x) != static_cast<int>(oldPosition.x))
	{
		currentPosition.x = oldPosition.x;

		velocity = Vector2<float>(0, velocity.y);
	}

	damage = 0;
}

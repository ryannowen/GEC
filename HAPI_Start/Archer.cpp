#include "Archer.h"

#include "World.h"
#include "Time.h"

Archer::Archer(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller>()))
{
}

void Archer::Update()
{
	ApplyPhysics();
}


void Archer::ApplyPhysics()
{
	const std::shared_ptr<Entity> player{ WORLD.GetPlayer() };

	Vector2<float> dir{ player->currentPosition - currentPosition };

	dir.Normalise();

	if (isGrounded)
	{
		isGrounded = false;
	}
	else
	{
		dir.y = 0;
		velocity.y += gravity * TIME.GetTickTimeSeconds(); /// Applies Gravity
	}

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
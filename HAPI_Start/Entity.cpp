#include "Entity.h"

#include "Renderer.h"
#include "Time.h"
#include "World.h"

size_t Entity::numOfEntities{ 0 };

Entity::Entity(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::shared_ptr<Controller>& argController)
	: spritePath(argSpritePath), spriteAnimData(argAnimData), collisionBounds(argCollisionBounds), entityController(argController)
{
	entityID = numOfEntities;
	numOfEntities++;
}

void Entity::Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage)
{
	if (entityController == nullptr)
	{
		std::cerr << "ERROR: Entity Controller is nullptr" << std::endl;
		return;
	}

	active = true;

	Vector2<float> pos{ argPosition };
	pos.y -= collisionBounds.bottom;
	currentPosition = pos;
	oldPosition = pos;

	speed = argSpeed;
	maxSpeed = argMaxSpeed;
	entityController->SetSide(argSide);
	health = argHealth;
	damage = argDamage;
}

void Entity::SwapControllerInput(std::shared_ptr<Entity> argEntity)
{
	entityController->SwapInput(*argEntity->entityController);
}

bool Entity::CheckCollision(const Entity& argEntity) const
{
	/// Returns false if entity is entity1
	if (!active || !argEntity.active || !hasCollision || !argEntity.hasCollision)
		return false;

	/// Editable copy of each bounds
	Rectangle tempCollisionBounds{ collisionBounds };
	Rectangle entityCollisionBounds{ argEntity.collisionBounds };

	/// Translates to screen space
	tempCollisionBounds.Translate(static_cast<int>(currentPosition.x), static_cast<int>(currentPosition.y));
	entityCollisionBounds.Translate(static_cast<int>(argEntity.currentPosition.x), static_cast<int>(argEntity.currentPosition.y));


	/// Checks if this has any of other entity inside it, or the opposite
	const bool collided{ (tempCollisionBounds.Contains(entityCollisionBounds) || entityCollisionBounds.Contains(tempCollisionBounds)) };

	/// Resets bounds to local space
	tempCollisionBounds.Translate(static_cast<int>(-currentPosition.x), static_cast<int>(-currentPosition.y));
	entityCollisionBounds.Translate(static_cast<int>(-argEntity.currentPosition.x), static_cast<int>(-argEntity.currentPosition.y));


	return collided;
}

void Entity::Collided(Entity& argEntity)
{
	/// Applies damage
	TakeDamage(argEntity);
	
	/// This entity
	if (!argEntity.passable)
	{
		if (currentPosition.y < argEntity.currentPosition.y)
		{
			isGrounded = true;
		}
		else
		{
			argEntity.isGrounded = true;
		}

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
	}
	
}

void Entity::AfterCollided(Entity& argEntity)
{
}

void Entity::OnDeath()
{
}

void Entity::OnAnimFinished()
{
}

void Entity::SetActive(const bool argActive)
{
	active = argActive;

	if (active)
		OnEnable();
	else
		OnDisable();
}

void Entity::OnDisable()
{
	spriteAnimData.currentSpriteCells.x = 0;
	velocity = Vector2<float>(0, 0);

	ResetEntity();
}

void Entity::OnEnable()
{
}

void Entity::Translate(Vector2<float>& argPosition)
{
	/// Updates old position for interpolation to be accurate and correct, then updates main position
	oldPosition = currentPosition;
	currentPosition += argPosition;
}

void Entity::ApplyPhysics(const Vector2<float> argDirection)
{
	acceleration += (argDirection * speed) * TIME.GetTickTimeSeconds();

	velocity += acceleration;

	if (velocity.x > maxSpeed)
		velocity.x = maxSpeed;
	else if (velocity.x < -maxSpeed)
		velocity.x = -maxSpeed;

	if (velocity.y > maxSpeed)
		velocity.y = maxSpeed;
	else if (velocity.y < -maxSpeed)
		velocity.y = -maxSpeed;

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

	if (static_cast<int>(velocity.y) != 0)
	{
		if (velocity.y > 0)
		{
			velocity.y -= drag * TIME.GetTickTimeSeconds();
			if (velocity.y < 0)
				velocity.y = 0;
		}
		else
		{
			velocity.y += drag * TIME.GetTickTimeSeconds();
			if (velocity.y > 0)
				velocity.y = 0;
		}
	}
	
	/// Applies gravity
	if (hasGravity)
	{
		velocity.y += gravity * TIME.GetTickTimeSeconds();
	}

	Translate(velocity * TIME.GetTickTimeSeconds());

	acceleration = Vector2<float>(0.0f, 0.0f);

	isGrounded = false;
}

bool Entity::TakeDamage(const Entity& argEntity)
{
	health -= argEntity.damage;

	if (health <= 0)
	{
		SetActive(false);
		OnDeath();
		return false;
	}


	return true;
}

bool Entity::CreateSprite(const bool argHasAlpha, const Vector2<unsigned int> argNumOfSpriteCells)
{
	return RENDERER.CreateSprite(spritePath, argHasAlpha, argNumOfSpriteCells);
}

void Entity::Draw(const float argInterp, const float argCameraOffset)
{
	/// Doesn't draw if entity is not active
	if (!active)
		return;

	if (spritePath == std::string())
		return;

	/// Calculates interpolation position to smoothly draw between the old and new position
	Vector2<float> newPosition{  (oldPosition + ((currentPosition - oldPosition) * argInterp)) };

	newPosition.x -= argCameraOffset;

	/// If sprite has animation then continues frames
	if (spriteAnimData.hasAnimation)
	{
		if (spriteAnimData.currentPlaybackTime >= spriteAnimData.GetCurrentPlaybackSpeed())
		{
			spriteAnimData.currentSpriteCells.x++;
			spriteAnimData.currentPlaybackTime = 0.0f;

			/// Wraps Sprite current cells between 0 and maximum number of cells for current animation
			if (spriteAnimData.currentSpriteCells.x > spriteAnimData.GetAnimNumOfCells() - 1)
			{
				spriteAnimData.currentSpriteCells.x = 0;

				if (!spriteAnimData.GetAnimShouldLoop())
				{
					OnAnimFinished();
				}					
			}
		}
		else
			spriteAnimData.currentPlaybackTime += TIME.GetDeltaTimeSeconds();
	}

	RENDERER.DrawSprite(spritePath, newPosition, spriteAnimData.currentSpriteCells);
}

void Entity::ResetEntity()
{
}

void Entity::AddVelocity(Vector2<float> argVelocity)
{
	velocity += argVelocity;
}

void Entity::AddAcceleration(Vector2<float> argAcceleration)
{
	acceleration += argAcceleration;
}

void Entity::SetVelocity(Vector2<float> argVelocity)
{
	velocity = argVelocity;
}

void Entity::SetAcceleration(Vector2<float> argAcceleration)
{
	acceleration = argAcceleration;
}
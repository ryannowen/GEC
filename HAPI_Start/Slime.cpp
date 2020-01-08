#include "Slime.h"

#include "Time.h"
#include "World.h"
#include "Audio.h"

void Slime::Attack()
{
	AUDIO.PlaySound(attackSound);
	velocity = Vector2<float>(0, 0);
	isAttacking = true;
	canAttack = false;
	damage = attackDamage;
}

void Slime::OnDeath()
{
	WORLD.IncreaseDefeatedEnemies();
	WORLD.AddScore(30);

	AUDIO.PlaySound(deathSound);
}

void Slime::OnAnimFinished()
{
	if (isAttacking)
	{
		isCharging = true;
		isAttacking = false;
		damage = 0;
	}
}

void Slime::OnDisable()
{
	if (isPossessed)
	{
		isPossessed = false;
		std::shared_ptr<Entity> opposingPlayer{ WORLD.GetOpposingPlayer() };

		SwapControllerInput(opposingPlayer);
		opposingPlayer->SetActive(true);
	}

	ResetEntity();
}


Slime::Slime(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller_Slime>()))
{
	AUDIO.LoadSound(attackSound, HAPI_TSoundOptions(0.5f));
	AUDIO.LoadSound(deathSound, HAPI_TSoundOptions(0.5f));

	isPossessable = true;
	passable = true;
	hasGravity = true;
}

void Slime::Update()
{
	/// Prevents input (Ai and Player) if possession isn't enabled
	if (WORLD.GetSceneState() != ESceneState::ePossession)
		return;

	entityController->Update(*this, 1);
	spriteAnimData.currentSpriteCells.y = static_cast<int>(entityController->GetAction());

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

	if (isPossessed && !isAttacking && !isCharging && canAttack)
	{
		Vector2<float> dir{ entityController->GetMovementDirection(1) };
		dir.y = 0;
		ApplyPhysics(dir);
	}
	else if (!isAttacking && !isCharging && canAttack)
	{
		const std::shared_ptr<Entity> player{ WORLD.GetPlayer() };
		Vector2<float> dir{ player->currentPosition - currentPosition };

		dir.Normalise();
		if (dir.y < 0 || !isGrounded)
			dir.y = 0;
		else
			dir.y = std::round(dir.y);

		dir.x = std::round(dir.x);

		ApplyPhysics(dir);
	}
	else
	{
		velocity = Vector2<float>(0, 0);
	}
}

void Slime::Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage)
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
	attackDamage = argDamage;
}

void Slime::AfterCollided(Entity& argEntity)
{
	if (argEntity == *WORLD.GetPlayer())
		damage = 0;
}

void Slime::ResetEntity()
{
	isAttacking = false;
	canAttack = true;
	isCharging = false;

	reChargeDelay = 0;
}

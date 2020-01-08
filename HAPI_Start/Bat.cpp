#include "Bat.h"

#include "World.h"
#include "Time.h"
#include "Controller_Bat.h"

void Bat::Attack()
{
	velocity = Vector2<float>(0, 0);
	isCharging = true;
	canAttack = false;
	damage = attackDamage;
}

void Bat::OnDeath()
{
	WORLD.IncreaseDefeatedEnemies();
	WORLD.AddScore(10);
}


void Bat::OnDisable()
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

Bat::Bat(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller_Bat>()))

{
	isPossessable = true;
	passable = true;
}

void Bat::Update()
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
	else if (isPossessed && !isCharging && canAttack)
	{
		ApplyPhysics(entityController->GetMovementDirection(1));
	}
	else if (!isCharging && canAttack)
	{
		const std::shared_ptr<Entity> player{ WORLD.GetPlayer() };
		Vector2<float> dir{ player->currentPosition - currentPosition };

		dir.Normalise();

		dir.x = std::round(dir.x);
		dir.y = std::round(dir.y);

		ApplyPhysics(dir);
	}
	else
	{
		velocity = Vector2<float>(0, 0);
	}
}

void Bat::Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage)
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

void Bat::AfterCollided(Entity& argEntity)
{
	if (argEntity == *WORLD.GetPlayer())
		damage = 0;
}

void Bat::ResetEntity()
{
	canAttack = true;
	isCharging = false;

	reChargeDelay = 0;
}

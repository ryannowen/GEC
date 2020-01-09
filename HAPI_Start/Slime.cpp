#include "Slime.h"

#include "Time.h"
#include "World.h"
#include "Audio.h"

#include "Player_Opposing.h"

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
	/// Stops being possessed
	if (isPossessed)
	{
		std::shared_ptr<Player_Opposing> opposingPlayer{ std::static_pointer_cast<Player_Opposing>(WORLD.GetOpposingPlayer()) };
		opposingPlayer->StopPossessing();
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
	Vector2<float> dir(0, 0);

	/// Prevents input (Ai and Player) if possession isn't enabled
	if (WORLD.GetSceneState() != ESceneState::ePossession)
	{
		ApplyPhysics(dir);
		return;
	}

	/// Updates controller
	entityController->Update(*this, playerID);
	spriteAnimData.currentSpriteCells.y = static_cast<int>(entityController->GetAction());


	if (isCharging) /// Increases charge delay
	{
		spawnDelay += TIME.GetTickTimeSeconds();

		if (spawnDelay >= spawnChargeTime)
		{
			spawnDelay = 0;
			isCharging = false;
			canAttack = true;
		}
	}
	else if (isPossessed && !isAttacking && !isCharging && canAttack) /// Moves in player direction
	{
		dir = entityController->GetMovementDirection(playerID);
		dir.y = 0;
	}
	else if (!isAttacking && !isCharging && canAttack) /// AI move to player
	{
		const std::shared_ptr<Entity>& player{ WORLD.GetPlayer() };
		dir = player->GetPosition() - currentPosition;

		dir.Normalise();
		dir.y = 0;

		dir.x = std::round(dir.x);
	}
	else
	{
		dir = Vector2<float>(0, 0);
	}

	ApplyPhysics(dir);

}

void Slime::Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage)
{
	if (entityController == nullptr)
	{
		std::cerr << "ERROR: Entity Controller is nullptr" << std::endl;
		return;
	}

	SetActive(true);

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

	spawnDelay = 0;
}

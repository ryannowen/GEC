#include "Bat.h"

#include "World.h"
#include "Time.h"
#include "Audio.h"

#include "Controller_Bat.h"
#include "Player_Opposing.h"

void Bat::Attack()
{
	velocity = Vector2<float>(0, 0);
	isCharging = true;
	canAttack = false;
	damage = attackDamage;
}

void Bat::OnDeath()
{
	AUDIO.PlaySound(deathSound);

	WORLD.IncreaseDefeatedEnemies();
	WORLD.AddScore(10);
}


void Bat::OnDisable()
{
	/// Stops being possessed
	if (isPossessed)
	{
		std::shared_ptr<Player_Opposing> opposingPlayer{ std::static_pointer_cast<Player_Opposing>(WORLD.GetOpposingPlayer()) };
		opposingPlayer->StopPossessing();
	}

	ResetEntity();
}

Bat::Bat(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller_Bat>()))

{
	AUDIO.LoadSound(deathSound, HAPI_TSoundOptions(1));

	isPossessable = true;
	passable = true;
}

void Bat::Update()
{
	/// Prevents input (Ai and Player) if possession isn't enabled
	if (WORLD.GetSceneState() != ESceneState::ePossession)
		return;

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
	else if (isPossessed && !isCharging && canAttack) /// Moves in player direction
	{
		ApplyPhysics(entityController->GetMovementDirection(playerID));
	}
	else if (!isCharging && canAttack)  /// AI move to player
	{
		const std::shared_ptr<Entity>& player{ WORLD.GetPlayer() };
		Vector2<float> dir{ player->GetPosition() - currentPosition };

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

void Bat::AfterCollided(Entity& argEntity)
{
	if (argEntity == *WORLD.GetPlayer())
		damage = 0;
}

void Bat::ResetEntity()
{
	canAttack = true;
	isCharging = false;

	spawnDelay = 0;
}

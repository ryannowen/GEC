#include "Slime_Boss.h"

#include "World.h"
#include "Audio.h"
#include "Time.h"
#include "Player_Opposing.h"

void Slime_Boss::SlimelingDeath()
{
	health -= 1;

	if (health <= 0)
	{
		SetActive(false);
		OnDeath();
	}
}

bool Slime_Boss::Attack()
{
	/// Prevents spawning more slimelings than health
	if (spawnedSlimelings > maxHealth)
		return false;

	/// Spawns slimeling
	Entity* slimeling;
	if (WORLD.SpawnEntity(ESpawnableEntities::eSlime_Slimeling, currentPosition, Vector2<float>(0, 0), entityController->GetSide(), speed, maxSpeed, 1, 1, &slimeling))
	{
		if (slimeling == nullptr)
			std::cerr << "ERROR: Slime boss attack recieved nullptr reference to slimeling" << std::endl;
		else
		{
			AUDIO.PlaySound(attackSound);

			isCharging = true;

			/// Updates slimeling to have reference
			static_cast<Slime_Slimeling*>(slimeling)->slimeBoss = this;
			spawnedSlimelings++;
			return true;
		}
	}

	return false;
}

void Slime_Boss::OnDeath()
{
	WORLD.IncreaseDefeatedEnemies();
	WORLD.AddScore(100);

	AUDIO.PlaySound(deathSound);
}

void Slime_Boss::OnDisable()
{
	/// Stops being possessed
	if (isPossessed)
	{
		std::shared_ptr<Player_Opposing> opposingPlayer{ std::static_pointer_cast<Player_Opposing>(WORLD.GetOpposingPlayer()) };
		opposingPlayer->StopPossessing();
	}

	ResetEntity();
}

bool Slime_Boss::TakeDamage(const Entity& argEntity)
{
	if (health <= 0)
		return false;

	return true;
}

Slime_Boss::Slime_Boss(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::make_shared<Controller_Slime_Boss>())
{
	AUDIO.LoadSound(attackSound, HAPI_TSoundOptions(0.5f));
	AUDIO.LoadSound(deathSound, HAPI_TSoundOptions(0.5f));

	isPossessable = true;
	passable = true;
	hasGravity = true;
}

void Slime_Boss::Update()
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
		}
	}
	else if (isPossessed && !isCharging) /// Moves in player direction
	{
		dir = entityController->GetMovementDirection(playerID);
		dir.y = 0;
	}
	else if (!isCharging) /// AI move away from player
	{
		const std::shared_ptr<Entity>& player{ WORLD.GetPlayer() };
		dir = player->GetPosition() - currentPosition;

		dir.Normalise();
		dir.y = 0;

		dir.x = -std::round(dir.x);
	}
	else
	{
		velocity = Vector2<float>(0, 0);
	}

	ApplyPhysics(dir);
}

void Slime_Boss::Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage)
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
	maxHealth = argHealth;
	health = argHealth;
	attackDamage = argDamage;
}

void Slime_Boss::ResetEntity()
{
	isCharging = false;
	spawnedSlimelings = 0;

	spawnDelay = 0;
}

#include "Archer.h"

#include "World.h"
#include "Time.h"
#include "Audio.h"

#include "Controller_Archer.h"
#include "Player_Opposing.h"

bool Archer::Attack(const Vector2<float> argDirection)
{
	Vector2<float> attackPos{ currentPosition };
	attackPos.y = currentPosition.y + 12;

	Vector2<float> projSpeed(1000, 1000);
	projSpeed *= argDirection;

	/// Changes projectile spawn side
	if (argDirection.x > 0)
		attackPos.x = currentPosition.x + collisionBounds.right;
	else
		attackPos.x = currentPosition.x;
	
	/// Spawns projectile
	if (WORLD.SpawnEntity(ESpawnableEntities::eArcherProjectile, attackPos, Vector2<float>(0,0), entityController->GetSide(),projSpeed, 400, 0, attackDamage))
	{
		AUDIO.PlaySound(attackSound);

		canAttack = false;
		isAttacking = true;

		return true;
	}

	return false;
}

void Archer::OnDeath()
{
	AUDIO.PlaySound(deathSound);

	WORLD.IncreaseDefeatedEnemies();
	WORLD.AddScore(50);
}

void Archer::OnAnimFinished()
{
	if (isAttacking)
	{
		isAttacking = false;
		isCharging = true;
	}
}

void Archer::OnDisable()
{
	/// Stops being possessed
	if (isPossessed)
	{
		std::shared_ptr<Player_Opposing> opposingPlayer{ std::static_pointer_cast<Player_Opposing>(WORLD.GetOpposingPlayer()) };
		opposingPlayer->StopPossessing();
	}

	ResetEntity();
}

Archer::Archer(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller_Archer>()))
{
	AUDIO.LoadSound(attackSound, HAPI_TSoundOptions(1));

	isPossessable = true;
	passable = true;
	hasGravity = true;
}

void Archer::Update()
{
	ApplyPhysics(Vector2<float>(0, 0));

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

}

void Archer::Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage)
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

void Archer::ResetEntity()
{
	isAttacking = false;
	canAttack = true;
	isCharging = false;

	spawnDelay = 0;
}

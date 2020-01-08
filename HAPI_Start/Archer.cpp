#include "Archer.h"

#include "World.h"
#include "Time.h"

#include "Controller_Archer.h"

bool Archer::Attack(const Vector2<float> argDirection)
{
	Vector2<float> attackPos{ currentPosition };
	attackPos.y = currentPosition.y + 12;

	Vector2<float> projSpeed(1000, 1000);
	projSpeed *= argDirection;

	if (argDirection.x > 0)
		attackPos.x = currentPosition.x + collisionBounds.right;
	else
		attackPos.x = currentPosition.x;
	

	if (WORLD.SpawnEntity(ESpawnableEntities::eArcherProjectile, attackPos, Vector2<float>(0,0), entityController->GetSide(),projSpeed, 400, 0, attackDamage))
	{
		canAttack = false;
		isAttacking = true;

		return true;
	}

	return false;
}

void Archer::OnDeath()
{
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
	if (isPossessed)
	{
		isPossessed = false;
		std::shared_ptr<Entity> opposingPlayer{ WORLD.GetOpposingPlayer() };

		SwapControllerInput(opposingPlayer);
		opposingPlayer->SetActive(true);
	}

	ResetEntity();
}

Archer::Archer(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller_Archer>()))
{
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

}

void Archer::Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage)
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

void Archer::ResetEntity()
{
	isAttacking = false;
	canAttack = true;
	isCharging = false;

	reChargeDelay = 0;
}

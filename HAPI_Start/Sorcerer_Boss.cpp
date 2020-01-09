#include "Sorcerer_Boss.h"

#include "World.h"
#include "Time.h"
#include "Audio.h"

bool Sorcerer_Boss::Attack(const Vector2<float> argDirection)
{
	Vector2<float> attackPos{ currentPosition };
	attackPos.y = currentPosition.y + 12;

	Vector2<float> projectileSpeed(1000, 1000);

	/// Changes projectile spawn side
	if (argDirection.x > 0)
		attackPos.x = currentPosition.x + collisionBounds.right;
	else
		attackPos.x = currentPosition.x;

	Vector2<float> projSpeed{ projectileSpeed };
	Vector2<float> offset(0.1f, 0.1f);

	/// Projectile1
	projSpeed = projectileSpeed * argDirection;
	bool projectile1{ WORLD.SpawnEntity(ESpawnableEntities::ePlayerProjectile, attackPos, Vector2<float>(-50, -50), entityController->GetSide(), projSpeed, 400, 0, attackDamage) };

	/// Projectile2
	projSpeed = projectileSpeed * (argDirection + offset);
	bool projectile2{ WORLD.SpawnEntity(ESpawnableEntities::eSorcererProjectile, attackPos, Vector2<float>(-50, -50), entityController->GetSide(), projSpeed, 400, 0, attackDamage) };

	/// Projectile3
	projSpeed = projectileSpeed * (argDirection - offset);
	bool projectile3{ WORLD.SpawnEntity(ESpawnableEntities::eSorcererProjectile, attackPos, Vector2<float>(-50, -50), entityController->GetSide(), projSpeed, 400, 0, attackDamage) };

	/// Begins charging if any projectile spawned
	if (projectile1 || projectile2 || projectile3)
	{
		AUDIO.PlaySound(attackSound);

		canAttack = false;
		isAttacking = true;

		return true;
	}

	return false;
}

void Sorcerer_Boss::OnDeath()
{
	AUDIO.PlaySound(deathSound);

	WORLD.IncreaseDefeatedEnemies();
	WORLD.AddScore(100);
}


Sorcerer_Boss::Sorcerer_Boss(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	:	Sorcerer(argSpritePath, argAnimData, argCollisionBounds, std::make_shared<Controller_Sorcerer_Boss>())
{
}

void Sorcerer_Boss::Update()
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

	ApplyPhysics(dir);

}

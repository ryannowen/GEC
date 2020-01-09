#include "Player.h"

#include "Time.h"

#include "World.h"
#include "Renderer.h"
#include "Audio.h"
#include "Tile.h"
#include "Controller_Player.h"


bool Player::Attack()
{
	if (canAttack && !isAttacking && WORLD.GetSceneState() == ESceneState::ePossession)
	{
		Vector2<float> attackPos{ currentPosition };

		Vector2<float> projSpeed(1000, 0);

		if (entityController->GetFacingDirection())
			attackPos.x = currentPosition.x + collisionBounds.right;
		else
		{
			projSpeed.x = -projSpeed.x;
			attackPos.x = currentPosition.x;
		}


		if (WORLD.SpawnEntity(ESpawnableEntities::ePlayerProjectile, attackPos, Vector2<float>(0, -25), entityController->GetSide(), projSpeed, 400, 0, projectileDamage))
		{
			AUDIO.PlaySound(attackSound);

			canAttack = false;
			isAttacking = true;
	
			return true;
		}
	}

	return false;
}

void Player::OnDeath()
{
	WORLD.SwitchPlayers();
	health = maxHealth;
	SetActive(true);
}

void Player::OnAnimFinished()
{
	const EAction& currentAction{ entityController->GetAction() };

	if (isAttacking)
		isAttacking = false;
}

void Player::ApplyPhysics(const Vector2<float> argDirection)
{
	acceleration += (argDirection * speed) * TIME.GetTickTimeSeconds();

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

	if (entityController->GetIsJumping(playerID) && isGrounded)
	{
		velocity.y -= speed.y * TIME.GetTickTimeSeconds(); /// Applies Jump force
		isGrounded = false;
	}
	else if(hasGravity)
	{
		velocity.y += gravity * TIME.GetTickTimeSeconds();
	}

	Translate(velocity * TIME.GetTickTimeSeconds());

	acceleration = Vector2<float>(0.0f, 0.0f);

	isGrounded = false;
}

Player::Player(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::vector<int>& argKeyboardMovementKeys, const std::vector<int>& argControllerMovementKeys)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::static_pointer_cast<Controller>(std::make_shared<Controller_Player>()))
{
	/// Creates playe2 sprite
	RENDERER.CreateSprite("Data//Player2.png", true, spriteAnimData.GetSpriteSheetSize());
	AUDIO.LoadSound(attackSound, HAPI_TSoundOptions(1));

	entityController->SetKeyboardInput(argKeyboardMovementKeys);
	entityController->SetControllerInput(argControllerMovementKeys);

	playerID = 0;

	passable = true;
	hasGravity = true;
}

void Player::Update()
{
	/// Updates current sprite animation depending on state

	entityController->Update(*this, playerID);
	spriteAnimData.currentSpriteCells.y = static_cast<int>(entityController->GetAction());

	/// Increases attack recharge delay, also allows for attacking if enough time has passed
	if (!canAttack)
	{
		attackDelay += TIME.GetTickTimeSeconds();

		if (attackDelay >= attackChargeTime)
		{
			canAttack = true;
			attackDelay = 0;
		}
	}

	
	Vector2<float> playerDir{ entityController->GetMovementDirection(playerID) };
	playerDir.y = 0;

	ApplyPhysics(playerDir);
}

void Player::Init(const Vector2<float>& argPosition, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage)
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
	maxHealth = argHealth;
	projectileDamage = argDamage;
}

void Player::ResetEntity()
{
	maxHealth = 10;
	projectileDamage = 1;

	attackDelay = 0;
	attackChargeTime = 1;
	canAttack = true;
	isAttacking = false;
}

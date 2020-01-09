#include "Player_Opposing.h"

#include "Controller_OpposingPlayer.h"

#include "Time.h"
#include "World.h"
#include "Audio.h"

void Player_Opposing::PlaceEntity()
{
	WORLD.PlaceEntity(currentPlacement, currentPosition);
}

void Player_Opposing::PossessEntity()
{
	WORLD.SpawnEntity(ESpawnableEntities::ePossession, currentPosition, Vector2<float>(0, 0), ESide::eEnvironment);
}

void Player_Opposing::ChangePlacementEntity()
{
	int newPlacement{ static_cast<int>(currentPlacement) + 1 };

	if (newPlacement >= static_cast<int>(ESpawnableEntities::ePossessablesCount))
		newPlacement = 0;

	currentPlacement = static_cast<ESpawnableEntities>(newPlacement);
}

void Player_Opposing::ApplyPhysics(const Vector2<float> argDirection)
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


	Translate(velocity * TIME.GetTickTimeSeconds());

	acceleration = Vector2<float>(0.0f, 0.0f);

}

Player_Opposing::Player_Opposing(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds, const std::vector<int>& argKeyboardMovementKeys, const std::vector<int>& argControllerMovementKeys)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::static_pointer_cast<Controller>(std::make_shared<Controller_OpposingPlayer>()))

{
	entityController->SetKeyboardInput(argKeyboardMovementKeys);
	entityController->SetControllerInput(argControllerMovementKeys);

	playerID = 1;

	hasCollision = false;
	passable = true;

	AUDIO.LoadSound(possessionSoundPath, HAPI_TSoundOptions(1));
}

void Player_Opposing::Update()
{
	entityController->Update(*this, playerID);

	ApplyPhysics(entityController->GetMovementDirection(playerID));

	if (!canAction)
	{
		actionDelay += TIME.GetTickTimeSeconds();

		if (actionDelay >= actionDelayTime)
		{
			actionDelay = 0;
			canAction = true;
		}
	}
}

void Player_Opposing::Collided(Entity& argEntity)
{
}

void Player_Opposing::StopPossessing()
{
	/// Checks if any entity is being possessed
	if (possessingEntity == nullptr)
		return;

	possessingEntity->SwapControllerInput(*this);
	possessingEntity->isPossessed = false;

	possessingEntity = nullptr;

	SetActive(true);
}

void Player_Opposing::BeginPossessing(Entity& argPossessing)
{
	if (possessingEntity != nullptr)
	{
		std::cerr << "ERROR: Trying to possess another entity when already possessing, argPossessEntityID=" << argPossessing.entityID << std::endl;
	}

	SwapControllerInput(argPossessing);
	argPossessing.isPossessed = true;

	possessingEntity = &argPossessing;

	AUDIO.PlaySound(possessionSoundPath);


	SetActive(false);
}

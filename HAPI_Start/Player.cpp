#include "Player.h"

#include "Time.h"

#include "World.h"
#include "Tile.h"
#include "Controller_Player.h"

unsigned int Player::numOfPlayers{ 0 };

void Player::OnAnimFinished()
{
	const EAction& currentAction{ entityController->GetAction() };
}

void Player::ApplyPhysics()
{
	Vector2<float> playerDir{ entityController->GetMovementDirection(playerID) };
	playerDir.y = 0;
	acceleration += (playerDir * speed) * TIME.GetTickTimeSeconds();


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

	if (entityController->isJumping(playerID) && isGrounded)
	{
		velocity.y -= speed.y * TIME.GetTickTimeSeconds(); /// Applies Jump force
		isGrounded = false;
	}
	else
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
	entityController->SetKeyboardInput(argKeyboardMovementKeys);
	entityController->SetControllerInput(argControllerMovementKeys);

	playerID = numOfPlayers;
	numOfPlayers++;

}

void Player::Update()
{
	/// Updates current sprite animation depending on state

	entityController->Update(*this, playerID);
	spriteAnimData.currentSpriteCells.y = static_cast<int>(entityController->GetAction());

	/// Increases attack recharge delay, also allows for attacking if enough time has passed
	if (!attackReady)
	{
		attackDelay += TIME.GetTickTimeSeconds();

		if (attackDelay >= attackChargeTime)
		{
			attackReady = true;
			attackDelay = 0;
		}
	}

	ApplyPhysics();




	// TODO Remove
	const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };
	const HAPI_TMouseData& mouseData{ HAPI.GetMouseData() };

	if (keyboardData.scanCode[HK_RETURN])
	{
		WORLD.level->Save("Data//Scenes.xml");
	}
	else if (keyboardData.scanCode[HK_NUMPAD8] && cellLoc.y != 0)
		cellLoc.y--;
	else if (keyboardData.scanCode[HK_NUMPAD5])
	{
		cellLoc.y++;
		if (cellLoc.y > 8)
			cellLoc.y = 8;
	}

	if (keyboardData.scanCode[HK_NUMPAD4] && cellLoc.x != 0)
		cellLoc.x--;
	else if (keyboardData.scanCode[HK_NUMPAD6])
	{
		cellLoc.x++;
		if (cellLoc.x > 7)
			cellLoc.x = 7;
	}

	if (mouseData.leftButtonDown || mouseData.rightButtonDown)
	{
		std::string spritePath;
		Vector2<int> cellCount(1,1);

		if (mouseData.leftButtonDown)
		{
			spritePath = "Data//Assets_Fast.png";
			cellCount = Vector2<int>(8, 9);
		}
		else if (mouseData.rightButtonDown)
		{
			cellCount = Vector2<int>(7, 8);
			spritePath = "Data//Assets_Alpha.png";
		}



		Vector2<float> position(0.0f, 0.0f);

		position.x = ((static_cast<int>(mouseData.x + WORLD.cameraOffset)) / 32) * 32.0f;
		position.y = (mouseData.y / 32) * 32.0f;

		std::shared_ptr<Scene> currentScene{ WORLD.GetScene(WORLD.currentSceneName) };


		for (std::shared_ptr<Entity> entity : currentScene->entities)
		{
			if (entity->GetSide() == ESide::eEnvironment)
			{
				if ((static_cast<int>(entity->currentPosition.x) == static_cast<int>(position.x)) && (static_cast<int>(entity->currentPosition.y) == static_cast<int>(position.y)))
				{
					cellLoc = entity->spriteAnimData.currentSpriteCells;
					std::cout << "Selected At : X=" << position.x << "  Y=" << position.y << std::endl;

					return;
				}

			}
		}

		if (static_cast<int>(position.x) != previousOffset.x || static_cast<int>(position.y) != previousOffset.y)
		{
			spawnedAmount++;


			previousOffset.x = static_cast<int>(position.x);
			previousOffset.y = static_cast<int>(position.y);

			std::cout << "Spawned At : X=" << position.x << "  Y=" << position.y << "  Amount=" << spawnedAmount << std::endl;


			WORLD.SpawnEntity(WORLD.currentSceneName, std::static_pointer_cast<Entity>(std::make_shared<Tile>(spritePath, AnimationData(std::vector<float>{0.0f}, std::vector<unsigned int>{1}, std::vector<bool>{false}, cellLoc, false))), false, cellCount);
			currentScene->entities.back()->Init(position, Vector2<float>(0, 0), ESide::eEnvironment, 0, 0);

			CHapiXMLNode* node = new CHapiXMLNode("Tile");

			node->AddAttribute(CHapiXMLAttribute("XLoc", std::to_string(position.x)));
			node->AddAttribute(CHapiXMLAttribute("YLoc", std::to_string(position.y)));
			node->AddAttribute(CHapiXMLAttribute("SpritePath", spritePath));
			node->AddAttribute(CHapiXMLAttribute("XCellLoc", std::to_string(cellLoc.x)));
			node->AddAttribute(CHapiXMLAttribute("YCellLoc", std::to_string(cellLoc.y)));
			node->AddAttribute(CHapiXMLAttribute("XTotalCells", std::to_string(cellCount.x)));
			node->AddAttribute(CHapiXMLAttribute("YTotalCells", std::to_string(cellCount.y)));
			node->AddAttribute(CHapiXMLAttribute("Health", std::to_string(0)));
			node->AddAttribute(CHapiXMLAttribute("Damage", std::to_string(0)));

			std::vector<CHapiXMLNode*> scenes{ WORLD.level->GetAllNodesWithName("Scene") };

			for (CHapiXMLNode* scene : scenes)
			{
				if (scene->GetAttributes()[0].AsString() == WORLD.currentSceneName)
				{
					scene->AddChild(node);
					break;
				}
			}
		}
	}
	///////////
}

bool Player::Attack()
{
	if (attackReady && GetActive())
	{
		attackReady = false;

		Vector2<float> attackPos{ currentPosition };
		Vector2<float> projSpeed(1000, 0);

		if (entityController->GetFacingDirection())
			attackPos.x = currentPosition.x + collisionBounds.right;
		else
		{
			projSpeed.x = -projSpeed.x;
			attackPos.x = currentPosition.x;
		}
		
		attackPos.y = currentPosition.y + 12;
		WORLD.FirePlayerProjectile(attackPos, projSpeed, entityController->GetSide(), damage);

		return true;
	}
	else
		return false;
}
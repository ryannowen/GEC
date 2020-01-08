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

	if (entityController->GetIsJumping(0) && isGrounded)
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

	passable = true;
	hasGravity = true;
}

void Player::Update()
{
	/// Updates current sprite animation depending on state

	entityController->Update(*this, 0);
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

	
	Vector2<float> playerDir{ entityController->GetMovementDirection(0) };
	playerDir.y = 0;

	ApplyPhysics(playerDir);
	



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

	bool remove{ false };

	if (mouseData.middleButtonDown)
		remove = true;

	if (mouseData.leftButtonDown || mouseData.rightButtonDown || remove)
	{
		std::string spritePath;
		Vector2<unsigned int> cellCount(1,1);

		if (mouseData.leftButtonDown)
		{
			spritePath = "Data//Assets_Fast.png";
			cellCount = Vector2<unsigned int>(8, 9);
		}
		else if (mouseData.rightButtonDown)
		{
			cellCount = Vector2<unsigned int>(7, 8);
			spritePath = "Data//Assets_Alpha.png";
		}



		Vector2<float> mousePosition(0.0f, 0.0f);

		mousePosition.x = ((mouseData.x + static_cast<int>(WORLD.cameraOffset)) / 32) * 32.0f;
		mousePosition.y = 32 + (mouseData.y / 32) * 32.0f;

		std::shared_ptr<Scene> currentScene{ WORLD.GetScene() };


		for (std::shared_ptr<Entity>& entity : currentScene->entities)
		{
			if (entity->GetSide() == ESide::eEnvironment)
			{
				if ((static_cast<int>(entity->currentPosition.x) == static_cast<int>(mousePosition.x)) && (static_cast<int>(entity->currentPosition.y) == static_cast<int>(mousePosition.y - 32)))
				{
					if (remove)
					{
						std::vector<CHapiXMLNode*> scenes{ WORLD.level->GetAllNodesWithName("Scene") };

						for (CHapiXMLNode* scene : scenes)
						{
							std::vector<CHapiXMLAttribute> sceneAtts{scene->GetAttributes()};
							if (sceneAtts[0].AsString() == WORLD.currentSceneName)
							{
								std::vector<CHapiXMLNode*> tiles{ scene->GetChildren() };

								for (CHapiXMLNode* tile : tiles)
								{
									std::vector<CHapiXMLAttribute> tileAtts{ tile->GetAttributes() };

									if (tileAtts[0].AsInt() == static_cast<int>(entity->currentPosition.x) && tileAtts[1].AsInt() == static_cast<int>(entity->currentPosition.y + 32))
									{
										tile->AddAttribute(CHapiXMLAttribute("REMOVE ME", "REMOVE ME"));
										entity->SetSpritePath("");
										std::cerr << "Found Tile to remove" << std::endl;
										return;
									}
								}
							}
						}
					}
					else
					{
						cellLoc = entity->spriteAnimData.currentSpriteCells;

						std::cout << "Selected At : X=" << mousePosition.x << "  Y=" << mousePosition.y << std::endl;
					}
					return;
				}

			}
		}

		if (static_cast<int>(mousePosition.x) != previousOffset.x || static_cast<int>(mousePosition.y) != previousOffset.y)
		{
			spawnedAmount++;


			previousOffset.x = static_cast<int>(mousePosition.x);
			previousOffset.y = static_cast<int>(mousePosition.y);

			std::cout << "Spawned At : X=" << mousePosition.x << "  Y=" << mousePosition.y << "  Amount=" << spawnedAmount << std::endl;


			WORLD.CreateEntity(WORLD.currentSceneName, std::static_pointer_cast<Entity>(std::make_shared<Tile>(spritePath, AnimationData(cellCount, std::vector<float>{0.0f}, std::vector<unsigned int>{1}, std::vector<bool>{false}, cellLoc, false))), false);
			currentScene->entities.back()->Init(mousePosition, ESide::eEnvironment, Vector2<float>(0, 0), 0, 0, 0);

			CHapiXMLNode* node = new CHapiXMLNode("Tile");

			node->AddAttribute(CHapiXMLAttribute("XLoc", std::to_string(mousePosition.x)));
			node->AddAttribute(CHapiXMLAttribute("YLoc", std::to_string(mousePosition.y)));
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

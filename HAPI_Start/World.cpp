#include "World.h"

#include <fstream>

/// My Headers
#include "Renderer.h"
#include "Time.h"
#include "UI_Interface.h"
#include "Audio.h"

#include "Player.h"
#include "Player_Opposing.h"
#include "Tile.h"
#include "TriggerBox.h"
#include "Archer.h"

#include "Slime.h"
#include "Slime_Explosive.h"
#include "Slime_Slimeling.h"
#include "Slime_Boss.h"

#include "Bat.h"

#include "Sorcerer.h"
#include "Sorcerer_Boss.h"

#include "Projectile.h"
#include "Projectile_Fireball.h"

#include "Explosion.h"
#include "Possession.h"

/// UI
#include "UI_Window_HUD.h"
#include "UI_Window_MainMenu.h"
#include "UI_Window_PauseMenu.h"
#include "UI_Window_ScoreScreen.h"
#include "UI_Window_Reward.h"
#include "UI_Window_EndScreen.h"



std::shared_ptr<World> World::world{ nullptr };

World::World()
{
	RENDERER.CreateWindow(Vector2<int>(1600, 900), "Ryan Robson T7091365");

	/// Loads Game Data
	LoadScenes();
	LoadGameData();

	/// Creates UI
	UI.CreateWindow("HUD", std::make_shared<UI_Window_HUD>(Vector2<float>(0, 0)));
	UI.CreateWindow("MainMenu", std::make_shared<UI_Window_MainMenu>(Vector2<float>(0, 0)));
	UI.SetWindowActive("MainMenu", true);

	UI.CreateWindow("PauseMenu", std::make_shared<UI_Window_PauseMenu>(Vector2<float>(0, 0)));
	UI.CreateWindow("ScoreScreen", std::make_shared<UI_Window_ScoreScreen>(Vector2<float>(0, 0)));
	UI.CreateWindow("RewardScreen", std::make_shared<UI_Window_Reward>(Vector2<float>(0, 0)));
	UI.CreateWindow("EndScreen", std::make_shared<UI_Window_EndScreen>(Vector2<float>(0, 0)));
}

void World::CreateEntity(const std::string& argSceneName, std::shared_ptr<Entity>& argEntity, const bool argHasAlpha)
{
	if (scenes.find(argSceneName) == scenes.end())
	{
		std::cerr << "ERROR: Couldn't find specified scene" << std::endl;
		return;
	}
	else
	{
		/// Adds entity to scene vector
		scenes.find(argSceneName)->second->CreateEntity(argEntity, argHasAlpha, argEntity->spriteAnimData.GetSpriteSheetSize());
	}
}

void World::Update()
{
	/// HAPI Update Loop
	while (HAPI.Update())
	{
		TIME.Update();

		/// Clears screen to black
		RENDERER.ClearScreen(HAPI_TColour::BLACK);

		if (worldState == EWorldState::eQuit)
		{
			HAPI.Close();
			return;
		}

		/// Gets Scenes
		std::shared_ptr<Scene>& globalScene{ GetScene("Global") };
		std::shared_ptr<Scene>& currentScene{ GetScene(currentSceneName) };

		const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

		if (keyboardData.scanCode[HK_ESCAPE] && worldState == EWorldState::eInGame)
			ChangeWorldState(EWorldState::ePauseMenu);


		/// Updates scenes
		const bool hasTicked{ TIME.GetHasTicked() };
		if (worldState == EWorldState::eInGame)
		{
			if (hasTicked)
			{
				/// Updates Scenes
				globalScene->UpdateScene();
				currentScene->UpdateScene();

				/// Scenes checks collisions against self, and other scene
				globalScene->CheckCollisions();
				currentScene->CheckCollisions();
				globalScene->CheckCollisions(currentScene);
			}

			/// Camera
			/// 1568 is the 1600 screen final tile
			float CameraArea{ currentScene->GetLevelLength() - 1568.0f };
			Vector2<float> playerPosition{ GetPlayer()->GetPosition() };
			//if (((player->currentPosition.x) > 800 - CameraArea) && ((player->currentPosition.x) < 800 + CameraArea))
				cameraOffset = playerPosition.x - 800;


			if (cameraOffset < 0)
				cameraOffset = 0;
			else if (cameraOffset > CameraArea)
				cameraOffset = CameraArea;
		}

		/// Calculates Interpolation then clamps it between 0 and 1 for scaling purposes
		float interp{ TIME.CalculateInterp() };
		if (interp > 1)
			interp = 1;
		else if (interp < 0)
			interp = 0;

		currentScene->DrawScene(interp, cameraOffset);
		globalScene->DrawScene(interp, cameraOffset);
		

		AUDIO.Update();

		UI.UpdateWindows();
		UI.DrawWindows();
	}
}

void World::SwitchPlayers()
{
	std::shared_ptr<Entity>& player{ GetPlayer() };

	std::shared_ptr<Player_Opposing> opposingPlayer{ std::static_pointer_cast<Player_Opposing>(WORLD.GetOpposingPlayer()) };
	opposingPlayer->StopPossessing();

	player->SwapControllerInput(*opposingPlayer);
	
	if (player->GetSpritePath() == "Data//Player1.png")
	{
		player->SetSpritePath("Data//Player2.png");
	}
	else
	{
		player->SetSpritePath("Data//Player1.png");
	}
}

bool World::SpawnEntity(const ESpawnableEntities argEntity, const Vector2<float> argPosition, const Vector2<float> argPositionOffset, const ESide argSide, const Vector2<float>& argSpeed, const float argMaxSpeed, const int argHealth, const int argDamage, Entity** argPlacedEntityRef)
{
	std::shared_ptr<Scene>& globalScene{ GetScene("Global") };


	int numOfEntites{ 0 };
	size_t entityIndex{ 0 };
	bool ignoreActive{ false };

	switch (argEntity)
	{
	case ESpawnableEntities::eSlime:
		numOfEntites = numOfSlimes;
		entityIndex = slimeIndex;
		break;
		
	case ESpawnableEntities::eSlime_Explosive:
		numOfEntites = numOfExplosiveSlimes;
		entityIndex = explosiveSlimeIndex;
		break;

	case ESpawnableEntities::eSlime_Slimeling:
		numOfEntites = numOfSlimelingSlimes;
		entityIndex = SlimelingIndex;
		break;
		
	case ESpawnableEntities::eArcher:
		numOfEntites = numOfArchers;
		entityIndex = ArcherIndex;
		break;
		
	case ESpawnableEntities::eBat:
		numOfEntites = numOfBats;
		entityIndex = BatIndex;
		break;
		
	case ESpawnableEntities::eSorcerer:
		numOfEntites = numOfSorcerers;
		entityIndex = SorcererIndex;
		break;

	case ESpawnableEntities::eMagicExplosion:
		numOfEntites = numOfMagicExplosions;
		entityIndex = magicExplosionIndex;
		break;
		
	case ESpawnableEntities::eFireExplosion:
		numOfEntites = numOfFireExplosions;
		entityIndex = fireExplosionIndex;
		break;
		
	case ESpawnableEntities::eFlame:
		numOfEntites = numOfFlames;
		entityIndex = FlamesIndex;
		break;
		
	case ESpawnableEntities::ePlayerProjectile:
		numOfEntites = numOfPlayerProjectiles;
		entityIndex = playerProjectileIndex;
		break;
		
	case ESpawnableEntities::eArcherProjectile:
		numOfEntites = numOfArcherProjectiles;
		entityIndex = ArcherProjectileIndex;
		break;
		
	case ESpawnableEntities::eSorcererProjectile:
		numOfEntites = numOfSorcererProjectiles;
		entityIndex = SorcererProjectileIndex;
		break;
		
	case ESpawnableEntities::eVortex:
		numOfEntites = 1;
		entityIndex = vortexIndex;
		break;
		
	case ESpawnableEntities::ePossession:
		ignoreActive = true;
		numOfEntites = 1;
		entityIndex = possessionIndex;
		break;
		
	default:
		std::cerr << "ERROR: Trying to spawn entity but case isn't specified, enumSpawnableEntityID=" << static_cast<int>(argEntity) << std::endl;
		return false;
		break;

	}

	for (int i = 0; i < numOfEntites; i++)
	{
		if (!globalScene->entities[static_cast<size_t>(entityIndex) + i]->GetActive() || ignoreActive)
		{
			int health{ argHealth };
			if (health != 0)
				health += static_cast<int>(difficulty);

			std::shared_ptr<Entity> entity{ globalScene->entities[static_cast<size_t>(entityIndex) + i] };
			entity->Init(argPosition - argPositionOffset, argSide, argSpeed, argMaxSpeed, health, argDamage);
			
			if(argPlacedEntityRef != nullptr)
				(*argPlacedEntityRef) = &(*entity);

			return true;
		}
	}



	std::cerr << "Trying to spawn entity but all are active enumSpawnableEntitiesID=" << static_cast<int>(argEntity) << std::endl;
	return false;
}

void World::SpawnMiniBoss()
{
	std::shared_ptr<Scene>& globalScene{ GetScene("Global") };

	size_t boss{ bossIndex + rand() % numOfBosses };
	globalScene->entities[boss]->Init(Vector2<float>(736, 696), ESide::ePlayerBoss, Vector2<float>(300, 300), 200, 5 + static_cast<int>(difficulty), 4 );
}

void World::SpawnBoss()
{
	std::shared_ptr<Scene>& globalScene{ GetScene("Global") };
	
	size_t boss{ bossIndex + rand() % numOfBosses };
	globalScene->entities[boss]->Init(Vector2<float>(736, 696), ESide::ePlayerBoss, Vector2<float>(500, 7500), 500, 10 + static_cast<int>(difficulty), 6);
}

void World::PlaceEntity(const ESpawnableEntities argEnemyType, const Vector2<float> argPosition)
{
	/// Returns because no more enemies are allowed
	if (placedEnemies >= maxPlaceEnemies)
		return;

	size_t index{ 0 };
	int numOfObjects{ 0 };
	Vector2<float> speed(0, 0);
	float maxSpeed{ 0 };
	int health{ 0 };
	int damage{ 0 };

	switch (argEnemyType)
	{
	case ESpawnableEntities::eSlime:
		index = slimeIndex;
		numOfObjects = numOfSlimes;
		speed = Vector2<float>(200, 7500);
		maxSpeed = 400;
		health = 2;
		damage = 2;
		break;

	case ESpawnableEntities::eSlime_Explosive:
		index = explosiveSlimeIndex;
		numOfObjects = numOfExplosiveSlimes;
		speed = Vector2<float>(200, 7500);
		maxSpeed = 400;
		health = 1;
		damage = 1;
		break;

	case ESpawnableEntities::eArcher:
		index = ArcherIndex;
		numOfObjects = numOfArchers;
		speed = Vector2<float>(0, 0);
		maxSpeed = 0;
		health = 3;
		damage = 1;
		break;

	case ESpawnableEntities::eBat:
		index = BatIndex;
		numOfObjects = numOfBats;
		speed = Vector2<float>(300, 300);
		maxSpeed = 600;
		health = 1;
		damage = 1;
		break;

	case ESpawnableEntities::eSorcerer:
		index = SorcererIndex;
		numOfObjects = numOfSorcerers;
		speed = Vector2<float>(0, 0);
		maxSpeed = 0;
		health = 1;
		damage = 1;
		break;

	default:
		std::cerr << "ERROR: Trying to place entity but case isn't specified" << std::endl;
		break;
	}

	if(SpawnEntity(argEnemyType, argPosition, Vector2<float>(0, 0), ESide::ePlayerBoss, speed, maxSpeed, health, damage))
	{
		placedEnemies++;

		if (placedEnemies >= maxPlaceEnemies)
		{
			GetPlayer()->SetPosition(playerSpawn);
			GetPlayer()->SetActive(true);
			sceneState = ESceneState::ePossession;
		}
	}
}

bool World::LoadScenes()
{
	std::vector<int> player1KeyboardInput =
	{
		'W',
		'S',
		'D',
		'A',
		HK_SPACE,
		'E'
	};

	std::vector<int> controllerInput =
	{
		HK_ANALOGUE_LEFT_THUMB_Y,
		HK_ANALOGUE_LEFT_THUMB_X,
		HK_DIGITAL_A,
		HK_DIGITAL_B
		
	};

	std::vector<int> player2KeyboardInput =
	{
		'I',
		'K',
		'L',
		'J',
		'U',
		'O'
	};

	/// Creates global scene
	scenes["Global"] = std::make_shared<Scene>("Global", 0, ESceneType::eNone);

	std::shared_ptr<Scene>& globalScene{ GetScene("Global") };

	/// Creates Magic Explosions Pool
	for (int i = 0; i < numOfMagicExplosions; i++)
	{
		if (i == 0)
			magicExplosionIndex = globalScene->entities.size();

		std::shared_ptr<Entity> explosion{ std::make_shared<Explosion>("Data//MagicExplosion.png", AnimationData(Vector2<unsigned int>(61, 1), std::vector<float>{0.01f}, std::vector<unsigned int>{61}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0), true)) };
		CreateEntity("Global", explosion, true);
	}

	/// Creates Fire Explosions Pool
	for (int i = 0; i < numOfFireExplosions; i++)
	{
		if (i == 0)
			fireExplosionIndex = globalScene->entities.size();

		std::shared_ptr<Entity> explosion{ std::make_shared<Explosion>("Data//FireExplosion.png", AnimationData(Vector2<unsigned int>(61, 1), std::vector<float>{0.01f}, std::vector<unsigned int>{61}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0), true)) };
		CreateEntity("Global", explosion, true);
	}

	/// Creates Flames Pool
	for (int i = 0; i < numOfFlames; i++)
	{
		if (i == 0)
			FlamesIndex = globalScene->entities.size();

		std::shared_ptr<Entity> flame{ std::make_shared<Explosion>("Data//Flame.png", AnimationData(Vector2<unsigned int>(47, 1), std::vector<float>{0.1f}, std::vector<unsigned int>{61}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0), true), Rectangle(21, 0, 50, 0)) };
		CreateEntity("Global", flame, true);
	}

	/// Creates Player Projectiles Pool
	for (int i = 0; i < numOfPlayerProjectiles; i++)
	{
		if (i == 0)
			playerProjectileIndex = globalScene->entities.size();

		std::shared_ptr<Entity> initialProjectile{ std::make_shared<Projectile>("Data//PlayerAttack.png", AnimationData(Vector2<unsigned int>(3, 1), std::vector<float>{0.55f}, std::vector<unsigned int>{3}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0), true), Rectangle{38, 7, 13, 4}) };
		CreateEntity("Global", initialProjectile, true);
	}

	/// Creates Archer Projectiles Pool
	for (int i = 0; i < numOfArcherProjectiles; i++)
	{
		if (i == 0)
			ArcherProjectileIndex = globalScene->entities.size();

		std::shared_ptr<Entity> initialProjectile{ std::make_shared<Projectile>("Data//Arrow.png", AnimationData(Vector2<unsigned int>(1, 1), std::vector<float>{2}, std::vector<unsigned int>{1}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0), true), Rectangle{50, 15, 5, 3}) };
		CreateEntity("Global", initialProjectile, true);
	}

	/// Creates Sorcerer Projectiles Pool
	for (int i = 0; i < numOfSorcererProjectiles; i++)
	{
		if (i == 0)
			SorcererProjectileIndex = globalScene->entities.size();

		std::shared_ptr<Entity> initialProjectile{ std::make_shared<Projectile_Fireball>("Data//FireBall.png", AnimationData(Vector2<unsigned int>(1, 1), std::vector<float>{2}, std::vector<unsigned int>{1}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0), true), Rectangle{10, 0, 10, 0}) };
		CreateEntity("Global", initialProjectile, true);
	}

	/// Creates Archer Pool
	for (int i = 0; i < numOfArchers; i++)
	{
		if (i == 0)
			ArcherIndex = globalScene->entities.size();

		std::shared_ptr<Entity> archer{ std::make_shared<Archer>("Data//Archer.png", AnimationData(Vector2<unsigned int>(12, 6), std::vector<float>{0.1f, 0.1f, 0.1f, 0.1f, 0.15f, 0.15f}, std::vector<unsigned int>{2, 2, 12, 12, 6, 6}, std::vector<bool>{true, true, false, false, false, false }, Vector2<unsigned int>(0, 0), true), Rectangle{58, 0, 61, 0}) };
		CreateEntity("Global", archer, true);
	}

	/// Creates Slime Pool
	for (int i = 0; i < numOfSlimes; i++)
	{
		if (i == 0)
			slimeIndex = globalScene->entities.size();

		std::shared_ptr<Entity> slime{ std::make_shared<Slime>("Data//Slime_Grey.png", AnimationData(Vector2<unsigned int>(5, 6), std::vector<float>{0.1f, 0.1f, 0.1f, 0.1f, 0.15f, 0.15f}, std::vector<unsigned int>{4, 4, 4, 4, 5, 5}, std::vector<bool>{true, true, false, false, false, false }, Vector2<unsigned int>(0, 0), true), Rectangle{60, 0, 45, 0}) };
		CreateEntity("Global", slime, true);
	}

	/// Creates Explosive Slime Pool
	for (int i = 0; i < numOfExplosiveSlimes; i++)
	{
		if (i == 0)
			explosiveSlimeIndex = globalScene->entities.size();

		std::shared_ptr<Entity> explosiveSlime{ std::make_shared<Slime_Explosive>("Data//Slime_Pink.png", AnimationData(Vector2<unsigned int>(5, 6), std::vector<float>{0.1f, 0.1f, 0.1f, 0.1f, 0.15f, 0.15f}, std::vector<unsigned int>{4, 4, 4, 4, 5, 5}, std::vector<bool>{true, true, false, false, false, false }, Vector2<unsigned int>(0, 0), true), Rectangle{60, 0, 45, 0}) };
		CreateEntity("Global", explosiveSlime, true);
	}

	/// Creates Slimeling Pool
	for (int i = 0; i < numOfSlimelingSlimes; i++)
	{
		if (i == 0)
			SlimelingIndex = globalScene->entities.size();

		std::shared_ptr<Entity> slimelingSlime{ std::make_shared<Slime_Slimeling>("Data//Slime_Slimeling.png", AnimationData(Vector2<unsigned int>(5, 6), std::vector<float>{0.1f, 0.1f, 0.1f, 0.1f, 0.15f, 0.15f}, std::vector<unsigned int>{4, 4, 4, 4, 5, 5}, std::vector<bool>{true, true, false, false, false, false }, Vector2<unsigned int>(0, 0), true), Rectangle{60, 0, 45, 0}) };
		CreateEntity("Global", slimelingSlime, true);
	}

	/// Creates Bat Pool
	for (int i = 0; i < numOfBats; i++)
	{
		if (i == 0)
			BatIndex = globalScene->entities.size();

		std::shared_ptr<Entity> bat{ std::make_shared<Bat>("Data//Bat.png", AnimationData(Vector2<unsigned int>(4, 2), std::vector<float>{0.1f, 0.1f}, std::vector<unsigned int>{4, 4}, std::vector<bool>{true, true}, Vector2<unsigned int>(0, 0), true), Rectangle{44, 0, 44, 0}) };
		CreateEntity("Global", bat, true);
	}

	/// Creates Sorcerer Pool
	for (int i = 0; i < numOfSorcerers; i++)
	{
		if (i == 0)
			SorcererIndex = globalScene->entities.size();

		std::shared_ptr<Entity> sorcerer{ std::make_shared<Sorcerer>("Data//Sorcerer.png", AnimationData(Vector2<unsigned int>(6, 6), std::vector<float>{0.2f, 0.2f, 0.2f, 0.2f, 0.15f, 0.15f}, std::vector<unsigned int>{3, 3, 3, 3, 6, 6}, std::vector<bool>{true, true, false, false, false, false}, Vector2<unsigned int>(0, 0), true), Rectangle{90, 0, 180, 0}, std::make_shared<Controller_Sorcerer>()) };
		CreateEntity("Global", sorcerer, true);
	}


	previewTile1Index = globalScene->entities.size();
	std::shared_ptr<Entity> previewTile{ std::make_shared<Tile>("Data//Assets_Fast.png", AnimationData(Vector2<unsigned int>(8, 9), std::vector<float>{0.0f}, std::vector<unsigned int>{1}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0),  false), Rectangle(32, 0, 32, 0)) };
	CreateEntity("Global", previewTile, true);
	//previewTile->Init(Vector2<float>(0, 32), ESide::eEnvironment, Vector2<float>(0, 0), 0, 0, 0);

	previewTile2Index = globalScene->entities.size();
	std::shared_ptr<Entity> previewTile2{ std::make_shared<Tile>("Data//Assets_Alpha.png", AnimationData(Vector2<unsigned int>(7, 8), std::vector<float>{0.0f}, std::vector<unsigned int>{1}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0),  false), Rectangle(32, 0, 32, 0)) };
	CreateEntity("Global", previewTile2, true);
	//previewTile2->Init(Vector2<float>(32, 32), ESide::eEnvironment, Vector2<float>(0, 0), 0, 0, 0);

	/// Player1
	playerIndex = globalScene->entities.size();
	std::shared_ptr<Entity> player1{ std::make_shared<Player>("Data//Player1.png", AnimationData(Vector2<unsigned int>(9, 6), std::vector<float>{0.1f, 0.1f, 0.1f, 0.1f, 0.05f, 0.05f}, std::vector<unsigned int>{5, 5, 6, 6, 9, 9}, std::vector<bool>{true, true, false, false, false, false }, Vector2<unsigned int>(0, 0), true), Rectangle{66, 35, 50, 1}, player1KeyboardInput, controllerInput) };
	CreateEntity("Global", player1, true);
	player1->Init(playerSpawn, ESide::ePlayerCharacter, Vector2<float>(200, 7500), 400, 10, 1);
	player1->SetActive(false);

	/// Player2
	opposingPlayerIndex = globalScene->entities.size();
	std::shared_ptr<Entity> player2{ std::make_shared<Player_Opposing>("Data//Crosshair.png", AnimationData(Vector2<unsigned int>(1, 1), std::vector<float>{0}, std::vector<unsigned int>{1}, std::vector<bool>{0}, Vector2<unsigned int>(0, 0), false), Rectangle{0, 0, 0, 0}, player2KeyboardInput, controllerInput) };
	CreateEntity("Global", player2, true);
	player2->Init(Vector2<float>(500, 700), ESide::eNeutral, Vector2<float>(350, 350), 500, 0, 0);
	player2->SetActive(false);

	/// Vortex
	vortexIndex = globalScene->entities.size();
	std::shared_ptr<Entity> vortex{ std::make_shared<Vortex>("Data//vortex.png", AnimationData(Vector2<unsigned int>(61, 1), std::vector<float>{0.025f}, std::vector<unsigned int>{61}, std::vector<bool>{true}, Vector2<unsigned int>(0, 0), true), Rectangle{100, 0, 100, 0}) };
	CreateEntity("Global", vortex, true);

	/// Possession
	possessionIndex = globalScene->entities.size();
	std::shared_ptr<Entity> possession{ std::make_shared<Possession>() };
	CreateEntity("Global", possession, false);


	/// Bossess
	bossIndex = globalScene->entities.size();
	std::shared_ptr<Entity> batBoss{ std::make_shared<Bat>("Data//Bat_Boss.png", AnimationData(Vector2<unsigned int>(4, 2), std::vector<float>{0.2f, 0.2f}, std::vector<unsigned int>{4, 4}, std::vector<bool>{true, true}, Vector2<unsigned int>(0, 0), true), Rectangle{88, 0, 88, 0}) };
	CreateEntity("Global", batBoss, true);

	std::shared_ptr<Entity> slimeBoss{ std::make_shared<Slime_Boss>("Data//Slime_Boss.png", AnimationData(Vector2<unsigned int>(4, 6), std::vector<float>{0.1f, 0.1f, 0.1f, 0.1f, 0.15f, 0.15f}, std::vector<unsigned int>{4, 4, 4, 4, 3, 3}, std::vector<bool>{true, true, false, false, false, false }, Vector2<unsigned int>(0, 0), true), Rectangle{64, 0, 50, 0}) };
	CreateEntity("Global", slimeBoss, true);

	std::shared_ptr<Entity> archerBoss{ std::make_shared<Archer>("Data//Archer_Boss.png", AnimationData(Vector2<unsigned int>(12, 6), std::vector<float>{0.1f, 0.1f, 0.1f, 0.1f, 0.05f, 0.05f}, std::vector<unsigned int>{2, 2, 12, 12, 6, 6}, std::vector<bool>{true, true, false, false, false, false }, Vector2<unsigned int>(0, 0), true), Rectangle{116, 0, 122, 0}) };
	CreateEntity("Global", archerBoss, true);

	std::shared_ptr<Entity> sorcererBoss{ std::make_shared<Sorcerer_Boss>("Data//Sorcerer_Boss.png", AnimationData(Vector2<unsigned int>(6, 6), std::vector<float>{0.2f, 0.2f, 0.2f, 0.2f, 0.1f, 0.1f}, std::vector<unsigned int>{3, 3, 3, 3, 6, 6}, std::vector<bool>{true, true, false, false, false, false}, Vector2<unsigned int>(0, 0), true), Rectangle{135, 0, 270, 0}) };
	CreateEntity("Global", sorcererBoss, true);

	numOfBosses = globalScene->entities.size() - bossIndex;
	
	/// Loads Level from file
	std::shared_ptr<CHapiXML> level = std::make_shared<CHapiXML>("Data//Scenes.xml");
	if (!level->HasData())
		return false;
	

	/// Gets scenes
	CHapiXMLNode* sceneNodes{ level->GetFirstNodeWithName("Scenes") };
	const std::vector<CHapiXMLNode*>& scenesChildren{ sceneNodes->GetChildren() };

	/// Loads each scene
	for (CHapiXMLNode* scene : scenesChildren)
	{
		const std::vector<CHapiXMLAttribute>& sceneAttributes{ scene->GetAttributes() };

		/// Creates scene in map
		const std::string& sceneName{ sceneAttributes[0].AsString() };
		scenes[sceneName] = std::make_shared<Scene>(sceneName, sceneAttributes[2].AsInt(), static_cast<ESceneType>(sceneAttributes[3].AsInt()));

		/// Creates background for scene
		std::shared_ptr<Entity>& background{ std::static_pointer_cast<Entity>(std::make_shared<Tile>(sceneAttributes[1].AsString(), AnimationData(Vector2<unsigned int>(1, 1), std::vector<float>{0.0f}, std::vector<unsigned int>{1}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0),  false))) };
		CreateEntity(sceneName, background, false);
		background->Init(Vector2<float>(0, 0), ESide::eNeutral, Vector2<float>(0, 0), 0, 0, 0);

		/// Spawns tiles in scene
		std::shared_ptr<Scene>& currentScene{ GetScene(sceneName) };
		const std::vector<CHapiXMLNode*>& children{ scene->GetChildren() };
		for (const CHapiXMLNode* tile : children)
		{
			const std::vector<CHapiXMLAttribute>& atts{ tile->GetAttributes() };

			CreateEntity(sceneName, std::static_pointer_cast<Entity>(std::make_shared<Tile>(atts[2].AsString(), AnimationData(Vector2<unsigned int>(atts[5].AsInt(), atts[6].AsInt()), std::vector<float>{0.0f}, std::vector<unsigned int>{1}, std::vector<bool>{false}, Vector2<unsigned int>(atts[3].AsInt(), atts[4].AsInt()), false))), false);
			currentScene->entities.back()->Init(Vector2<float>(atts[0].AsFloat(), atts[1].AsFloat()), ESide::eEnvironment, Vector2<float>(0, 0), 0, atts[7].AsInt(), atts[8].AsInt());
		}
	}

	return true;
}

void World::ChangeScene(const std::string& argSceneName)
{
	if (scenes.find(argSceneName) != scenes.end())
	{
		std::cerr << "ERROR: Couldn't find scene, name=" << argSceneName << std::endl;
		return;
	}
	

	currentSceneName = argSceneName;
}

void World::ChangeScene(const ESceneType argSceneType)
{
	std::vector<std::shared_ptr<Scene>> matchingScenes;
	
	/// Finds scenes with same type
	for (auto& scene : scenes)
	{
		if (scene.second->GetSceneType() == argSceneType)
			matchingScenes.push_back(scene.second);
	}

	/// randomly selects scene if available
	if (matchingScenes.size() > 0)
		currentSceneName = matchingScenes[rand() % matchingScenes.size()]->GetSceneName();
	else
		std::cerr << "ERROR: No matching scenes found to change scene to" << std::endl;
}

void World::NextScene()
{
	std::shared_ptr<Entity>& player{ GetPlayer() };
	std::shared_ptr<Entity>& opposingPlayer{ GetOpposingPlayer() };

	player->SetPosition(playerSpawn);

	if (finalBoss) /// If final boss has been defeated, go to score screen
	{
		player->SetActive(false);
		opposingPlayer->SetActive(false);
		ChangeScene(ESceneType::eUI);
		ChangeWorldState(EWorldState::eEndScreen);
		SaveGameData();
		ResetGame();
		return;
	}
	else if (bossesDefeated >= requiredDefeatedBosses) /// if all required mini-bosses are killed take player to final boss room
	{
		opposingPlayer->SetActive(true);
		defatedEnemies = 0;
		placedEnemies = 1;
		maxPlaceEnemies++;
		finalBoss = true;
		sceneState = ESceneState::ePlacement;
		ChangeScene(ESceneType::eBoss);
		ChangeWorldState(EWorldState::eInGame);
		SpawnBoss();
		return;
	}

	const std::shared_ptr<Scene>& currentScene{ GetScene(currentSceneName) };

	switch (currentScene->GetSceneType())
	{
	case ESceneType::eBoss:
		player->SetActive(false);
		opposingPlayer->SetActive(false);
		defatedEnemies = 0;
		placedEnemies = 0;
		bossesDefeated++;
		sceneState = ESceneState::eNone;
		ChangeScene(ESceneType::eReward);
		ChangeWorldState(EWorldState::eRewardScreen);
		SpawnEntity(ESpawnableEntities::eVortex, Vector2<float>(768, 640), Vector2<float>(0, 0), ESide::eEnvironment);
		break;

	case ESceneType::eReward:
		opposingPlayer->SetActive(true);
		sceneState = ESceneState::ePlacement;
		ChangeScene(ESceneType::eTransition);
		ChangeWorldState(EWorldState::eInGame);
		break;

	case ESceneType::eTransition:
		opposingPlayer->SetActive(true);
		defatedEnemies = 0;
		placedEnemies = 1;
		maxPlaceEnemies++;
		sceneState = ESceneState::ePossession;
		ChangeScene(ESceneType::eBoss);
		SpawnMiniBoss();
		break;

	case ESceneType::eUI:
		opposingPlayer->SetActive(true);
		sceneState = ESceneState::ePlacement;
		ChangeScene(ESceneType::eTransition);
		ChangeWorldState(EWorldState::eInGame);
		break;

	default:
		std::cerr << "ERROR: Trying to change to next scene but case isn't specified, sceneEnumTypeID=" << static_cast<int>(currentScene->GetSceneType()) << std::endl;
		break;
	}
}

void World::ChangeWorldState(const EWorldState argState)
{
	switch (argState)
	{
	case EWorldState::eInGame:
		UI.HideAllWindows();
		UI.SetWindowActive("HUD", true);
		break;

	case EWorldState::eMainMenu:
		UI.HideAllWindows();
		UI.SetWindowActive("MainMenu", true);
		break;

	case EWorldState::ePauseMenu:
		UI.SetWindowActive("PauseMenu", true);
		break;

	case EWorldState::eQuit:
		HAPI.Close();
		break;

	case EWorldState::eScoreScreen:
		UI.HideAllWindows();
		UI.SetWindowActive("ScoreScreen", true);
		break;

	case EWorldState::eRewardScreen:
		UI.HideAllWindows();
		UI.SetWindowActive("RewardScreen", true);
		break;

	case EWorldState::eEndScreen:
		UI.HideAllWindows();
		UI.SetWindowActive("EndScreen", true);
		break;

	default:
		std::cerr << "ERROR: Trying to change world state but case is not specified" << std::endl;
		return;
		break;
	}

	worldState = argState;
}

void World::ResetGame()
{
	GetPlayer()->ResetEntity();
	score = 0;

	sceneState = ESceneState::ePlacement;
	finalBoss = false;
	bossesDefeated = 0;

	defatedEnemies = 0;
	placedEnemies = 0;
	maxPlaceEnemies = 2; /// Number of enemies opposing player is allowed to place
}

void World::IncreaseDefeatedEnemies()
{
	defatedEnemies++;

	if (defatedEnemies >= placedEnemies)
	{
		Vector2<float> vortexPosition(768, 672);

		if (GetScene()->GetSceneType() == ESceneType::eTransition)
			vortexPosition = Vector2<float>(1664, 704);

		SpawnEntity(ESpawnableEntities::eVortex, vortexPosition, Vector2<float>(0, 0), ESide::eEnvironment);
	}
}

void World::ChangeDifficulty()
{
	int dif{ static_cast<int>(difficulty) + 1 };

	if (dif >= static_cast<int>(EDifficulty::eCount))
		dif = 0;

	difficulty = static_cast<EDifficulty>(dif);
}

void World::SaveGameData()
{
	if (score > highScore)
	{
		highScore = score;
		hasNewHighScore = true;
	}


	std::ofstream file("Data//Game.data");
	if (file.is_open())
	{
		file << highScore << std::endl;
		file.close();
	}
	else
		std::cerr << "ERROR: Couldn't create file to save game data" << std::endl;
}

void World::LoadGameData()
{
	std::ifstream file("Data//Game.data");
	if (file.is_open())
	{
		std::string fileLine;

		while (std::getline(file, fileLine))
		{
			highScore = std::stoi(fileLine);
		}

		file.close();
	}
	else
		std::cerr << "ERROR: Couldn't load file to load game data" << std::endl;
}

std::shared_ptr<Entity> World::GetPlayer()
{
	return GetScene("Global")->entities[playerIndex];
}

std::shared_ptr<Entity> World::GetOpposingPlayer()
{
	return GetScene("Global")->entities[opposingPlayerIndex];
}


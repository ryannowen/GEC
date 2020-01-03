#include "World.h"

#include "Renderer.h"
#include "Time.h"

#include "Player.h"
#include "Tile.h"
#include "Projectile.h"
#include "TriggerBox.h"
#include "Archer.h"
#include "Slime.h"
#include "Slime_Explosive.h"
#include "Explosion.h"

std::shared_ptr<World> World::world{ nullptr };

World::World()
{
	RENDERER.CreateWindow(Vector2<int>(1600, 900), "Ryan Robson T7091365");

	LoadScenes();
}

void World::Update()
{
	/// HAPI Update Loop
	while (HAPI.Update())
	{
		TIME.Update();

		/// Clears screen to black
		RENDERER.ClearScreen(HAPI_TColour::BLACK);

		const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };
		if (keyboardData.scanCode['I'])
			ChangeScene(ESceneType::eTransition);

		/// Gets Scenes
		std::shared_ptr<Scene> globalScene{ GetScene("Global") };
		std::shared_ptr<Scene> currentScene{ GetScene(currentSceneName) };

		/// Updates scenes
		const bool hasTicked{ TIME.GetHasTicked() };
		if (hasTicked)
		{
			/// Updates Scenes
			globalScene->UpdateScene();
			currentScene->UpdateScene();

			/// Checks collisions against self, and other scene
			globalScene->CheckCollisions();
			currentScene->CheckCollisions();
			globalScene->CheckCollisions(currentScene);
		}

		/// Camera
		/// 1568 is the 1600 screen final tile
		int CameraArea{ currentScene->GetLevelLength() - 1568 };
		if (((globalScene->entities[2]->currentPosition.x) > 800 - CameraArea) && ((globalScene->entities[2]->currentPosition.x) < 800 + CameraArea))
			cameraOffset = globalScene->entities[2]->currentPosition.x - 800;


		if (cameraOffset < 0)
			cameraOffset = 0;
		else if (cameraOffset > CameraArea)
			cameraOffset = CameraArea;

		/// Gets Interpolation then clamps it between 0 and 1 for scaling purposes
		float interp{ TIME.CalculateInterp() };
		if (interp > 1)
			interp = 1;
		else if (interp < 0)
			interp = 0;

		currentScene->DrawScene(interp, cameraOffset);
		globalScene->DrawScene(interp, cameraOffset);
		
			
		////////////////// TODO Remove
		globalScene->entities[0]->spriteAnimData.currentSpriteCells = std::static_pointer_cast<Player>(globalScene->entities[2])->cellLoc;
		globalScene->entities[1]->spriteAnimData.currentSpriteCells = std::static_pointer_cast<Player>(globalScene->entities[2])->cellLoc;

		//HAPI.RenderText(10, 10, HAPI_TColour::RED, std::string("Cell Loc: X=" + std::to_string(std::static_pointer_cast<Player>(entities[3])->cellLoc.x)).append("  Y=" + std::to_string(std::static_pointer_cast<Player>(entities[3])->cellLoc.y)));
		///////////////////
	}
}

void World::FirePlayerProjectile(const Vector2<float>& argPosition, const Vector2<float>& argSpeed, const ESide argSide, const int argDamage)
{
	std::shared_ptr<Scene> globalScene{ GetScene("Global") };

	for (int i = 0; i < numOfPlayerProjectiles; i++)
	{
		if (!globalScene->entities[playerProjectilePoolIndex + i]->GetActive())
		{
			globalScene->entities[playerProjectilePoolIndex + i]->Init(argPosition, argSpeed, argSide, 0, 2);
			std::cout << "Fired ID: " << (playerProjectilePoolIndex + i) << std::endl; // TODO Remove
			return;
		}
	}
}

void World::SpawnExplosion(const Vector2<float>& argPosition)
{
	std::shared_ptr<Scene> globalScene{ GetScene("Global") };
	const Vector2<float> explosionSize(50, 50);

	for (int i = 0; i < numOfExplosions; i++)
	{
		if (!globalScene->entities[explosionIndex + i]->GetActive())
		{
			globalScene->entities[explosionIndex + i]->Init(argPosition - explosionSize, Vector2<float>(0, 0), ESide::eNeutral, 0, 0);
			
			std::cout << "Spawned Explosion ID=" << explosionIndex + i << std::endl;
			return;
		}
	}
}

void World::SpawnEntity(const std::string& argSceneName, std::shared_ptr<Entity>& argEntity, const bool argHasAlpha, const Vector2<int> argNumOfSpriteCells = Vector2<int>(1, 1))
{

	if (scenes.find(argSceneName) == scenes.end())
	{
		std::cerr << "ERROR: Couldn't find specified scene" << std::endl;
		return;
	}
	else
	{
		/// Adds entity to scene vector
		scenes.find(argSceneName)->second->SpawnEntity(argEntity, argHasAlpha, argNumOfSpriteCells);

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

	std::shared_ptr<Scene> globalScene{ GetScene("Global") };

	std::shared_ptr<Entity> previewTile{ std::static_pointer_cast<Entity>(std::make_shared<Tile>("Data//Assets_Fast.png", AnimationData(std::vector<float>{0.0f}, std::vector<unsigned int>{1}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0),  false), Rectangle(32, 0, 32, 0))) };
	std::shared_ptr<Entity> previewTile2{ std::static_pointer_cast<Entity>(std::make_shared<Tile>("Data//Assets_Alpha.png", AnimationData(std::vector<float>{0.0f}, std::vector<unsigned int>{1}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0),  false), Rectangle(32, 0, 32, 0))) };
	std::shared_ptr<Entity> player1{ std::static_pointer_cast<Entity>(std::make_shared<Player>("Data//Player1.png", AnimationData(std::vector<float>{0.1f, 0.1f, 0.1f, 0.1f, 0.05f, 0.05f}, std::vector<unsigned int>{5, 5, 6, 6, 9, 9}, std::vector<bool>{true, true, false, false, false, false }, Vector2<unsigned int>(0, 0), true), Rectangle{66, 35, 50, 1}, player1KeyboardInput, controllerInput)) };
	std::shared_ptr<Entity> player2{ std::static_pointer_cast<Entity>(std::make_shared<Player>("Data//Player2.png", AnimationData(std::vector<float>{0.1f, 0.1f, 0.1f, 0.1f, 0.05f, 0.05f}, std::vector<unsigned int>{5, 5, 6, 6, 9, 9}, std::vector<bool>{true, true, false, false, false, false }, Vector2<unsigned int>(0, 0), true), Rectangle{31, 0, 49, 0}, player2KeyboardInput, controllerInput)) };
	std::shared_ptr<Entity> slime{ std::static_pointer_cast<Entity>(std::make_shared<Slime_Explosive>("Data//Slime_Pink.png", AnimationData(std::vector<float>{0.1f, 0.1f, 0.1f, 0.1f, 0.15f, 0.15f}, std::vector<unsigned int>{4, 4, 4, 4, 5, 5}, std::vector<bool>{true, true, false, false, false, false }, Vector2<unsigned int>(0, 0), true), Rectangle{60, 0, 45, 0})) };
	std::shared_ptr<Entity> vortex{ std::static_pointer_cast<Entity>(std::make_shared<TriggerBox>("Data//vortex.png", AnimationData(std::vector<float>{0.025f}, std::vector<unsigned int>{61}, std::vector<bool>{true}, Vector2<unsigned int>(0, 0), true), Rectangle{100, 0, 100, 0})) };


	SpawnEntity("Global", previewTile, true, Vector2<int>(8, 9));
	SpawnEntity("Global", previewTile2, true, Vector2<int>(7, 8));

	playerIndex = globalScene->entities.size();
	SpawnEntity("Global", player1, true, Vector2<int>(9, 6));
	//SpawnEntity(player2, true, Vector2<int>(9, 6));
	SpawnEntity("Global", slime, true, Vector2<int>(5, 6));

	vortexIndex = globalScene->entities.size();
	SpawnEntity("Global", vortex, true, Vector2<int>(61, 1));


	previewTile->Init(Vector2<float>(0, 32), Vector2<float>(0, 0), ESide::eEnvironment, 0, 0);
	previewTile2->Init(Vector2<float>(32, 32), Vector2<float>(0, 0), ESide::eEnvironment, 0, 0);

	player1->Init(Vector2<float>(200, 730), Vector2<float>(200, 7500), ESide::ePlayerCharacter, 10, 0);
	//player2->Init(Vector2<float>(615, 200), Vector2<float>(200, 7500), ESide::ePlayerBoss, 10, 1);

	slime->Init(Vector2<float>(200, 500), Vector2<float>(200, 7500), ESide::ePlayerBoss, 10, 0);
		
	vortex->Init(Vector2<float>(800, 500), Vector2<float>(0, 0), ESide::eEnvironment, 0, 0);


	/// Creates Player Projectiles
	for (int i = 0; i < numOfPlayerProjectiles; i++)
	{
		if (i == 0)
			playerProjectilePoolIndex = globalScene->entities.size();

		std::shared_ptr<Entity> initialProjectile{ std::static_pointer_cast<Entity>(std::make_shared<Projectile>("Data//PlayerAttack.png", AnimationData(std::vector<float>{0.55f}, std::vector<unsigned int>{3}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0), true), Rectangle{38, 7, 5, 4})) };
		SpawnEntity("Global", initialProjectile, true, Vector2<int>(3, 1));
	}

	/// Creates Player Explosions
	for (int i = 0; i < numOfExplosions; i++)
	{
		if (i == 0)
			explosionIndex = globalScene->entities.size();

		std::shared_ptr<Entity> explosion{ std::static_pointer_cast<Entity>(std::make_shared<Explosion>("Data//MagicExplosion.png", AnimationData(std::vector<float>{0.01f}, std::vector<unsigned int>{61}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0), true))) };
		SpawnEntity("Global", explosion, true, Vector2<int>(61, 1));
	}


	/// Loads Level from file
	level = std::make_shared<CHapiXML>("Data//Scenes.xml");
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
		scenes[sceneName] = std::make_shared<Scene>(sceneAttributes[0].AsString(), sceneAttributes[2].AsInt(), static_cast<ESceneType>(sceneAttributes[3].AsInt()));

		/// Creates background for scene
		std::shared_ptr<Entity> background{ std::static_pointer_cast<Entity>(std::make_shared<Tile>(sceneAttributes[1].AsString(), AnimationData(std::vector<float>{0.0f}, std::vector<unsigned int>{1}, std::vector<bool>{false}, Vector2<unsigned int>(0, 0),  false))) };
		SpawnEntity(sceneName, background, false, Vector2<int>(1, 1));
		background->Init(Vector2<float>(0, 0), Vector2<float>(0, 0), ESide::eNeutral, 0, 0);

		/// Spawns tiles in scene
		std::shared_ptr<Scene> currentScene{ GetScene(sceneName) };
		const std::vector<CHapiXMLNode*>& children{ scene->GetChildren() };
		for (const CHapiXMLNode* tile : children)
		{
			const std::vector<CHapiXMLAttribute>& atts{ tile->GetAttributes() };

			SpawnEntity(sceneName, std::static_pointer_cast<Entity>(std::make_shared<Tile>(atts[2].AsString(), AnimationData(std::vector<float>{0.0f}, std::vector<unsigned int>{1}, std::vector<bool>{false}, Vector2<unsigned int>(atts[3].AsInt(), atts[4].AsInt()), false))), false, Vector2<int>(atts[5].AsInt(), atts[6].AsInt()));
			currentScene->entities.back()->Init(Vector2<float>(atts[0].AsFloat(), atts[1].AsFloat()), Vector2<float>(0, 0), ESide::eEnvironment, atts[7].AsInt(), atts[8].AsInt());
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
	for (auto scene : scenes)
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
	/// if all required mini-bosses are killed take player to final boss room
	if (bossesDefeated >= requiredDefeatedBosses)
	{
		ChangeScene(ESceneType::eBoss);
		return;
	}

	const std::shared_ptr<Scene> currentScene{ GetScene(currentSceneName) };

	switch (currentScene->GetSceneType())
	{
	case ESceneType::eBoss:
		bossesDefeated++;
		ChangeScene(ESceneType::eReward);
		break;

	case ESceneType::eReward:
		ChangeScene(ESceneType::eTransition);
		break;

	case ESceneType::eTransition:
		ChangeScene(ESceneType::eBoss);
		break;
	default:
		break;
	}
}

std::shared_ptr<Entity>& World::GetPlayer()
{
	return GetScene("Global")->entities[playerIndex];
}

std::shared_ptr<Entity>& World::GetVortex()
{
	return GetScene("Global")->entities[vortexIndex];
}


#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

#include <vector>
#include <iostream>
#include <unordered_map>

/// My Headers
#include "Vector2.h"
#include "Scene.h"


enum class ESide;
enum class EEnemyPlacement;

class Renderer;
class Entity;

// Difficulty for game
enum class EDifficulty
{
	eEasy,
	eNormal,
	eHard,
	eInsane,
	eImpossible,
	eExcessive,
	eStop,
	eFine,
	eBye,
	eCount
};

// State of world for game
enum class EWorldState
{
	eMainMenu,
	ePauseMenu,
	eInGame,
	eScoreScreen,
	eRewardScreen,
	eEndScreen,
	eQuit
};

// Scene state for sub-state of world
enum class ESceneState
{
	eNone,
	ePlacement,
	ePossession
};

// Types of entities which can be created, and possessed
enum class ESpawnableEntities
{
	eSlime,
	eSlime_Explosive,
	eArcher,
	eBat,
	eSorcerer,
	ePossessablesCount,
	eSlime_Slimeling,
	eMagicExplosion,
	eFireExplosion,
	eFlame,
	ePlayerProjectile,
	eArcherProjectile,
	eSorcererProjectile,
	eVortex,
	ePossession,
	ePlayer
};

class World
{
private:
	World();

	friend class UI_Window_HUD;

	static std::shared_ptr<World> world;
	EWorldState worldState{ EWorldState::eMainMenu };
	EDifficulty difficulty{ EDifficulty::eEasy };
	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
	
	Vector2<float> playerSpawn{ 64, 717 };

	bool hasNewHighScore{ false };
	unsigned int highScore{ 0 };
	unsigned int score{ 0 };

	ESceneState sceneState{ ESceneState::ePlacement };
	bool finalBoss{ false };
	unsigned short bossesDefeated{ 0 };
	unsigned short requiredDefeatedBosses{ 3 }; /// Number of mini-bosses before final boss

	unsigned short defatedEnemies{ 0 };
	unsigned short placedEnemies{ 0 };
	unsigned short maxPlaceEnemies{ 2 }; /// Number of enemies opposing player is allowed to place

	

	size_t playerIndex{ 0 };
	size_t opposingPlayerIndex{ 0 };
	size_t vortexIndex{ 0 };
	size_t possessionIndex{ 0 };

	const int numOfMagicExplosions{ 10 };
	size_t magicExplosionIndex{ 0 };

	const int numOfFireExplosions{ 5 };
	size_t fireExplosionIndex{ 0 };

	const int numOfFlames{ 15 };
	size_t FlamesIndex{ 0 };

	const int numOfPlayerProjectiles{ 10 };
	size_t playerProjectileIndex{ 0 };

	const int numOfArcherProjectiles{ 10 };
	size_t ArcherProjectileIndex{ 0 };

	const int numOfSorcererProjectiles{ 15 };
	size_t SorcererProjectileIndex{ 0 };

	const int numOfArchers{ 5 };
	size_t ArcherIndex{ 0 };

	const int numOfSlimes{ 5 };
	size_t slimeIndex{ 0 };

	const int numOfExplosiveSlimes{ 5 };
	size_t explosiveSlimeIndex{ 0 };

	const int numOfSlimelingSlimes{ 18 };
	size_t SlimelingIndex{ 0 };

	const int numOfBats{ 5 };
	size_t BatIndex{ 0 };

	const int numOfSorcerers{ 5 };
	size_t SorcererIndex{ 0 };

	size_t numOfBosses{ 0 };
	size_t bossIndex{ 0 };

	size_t previewTile1Index{ 0 };
	size_t previewTile2Index{ 0 };

	std::string currentSceneName{ "UI" };
	float cameraOffset{ 0 };

	// Creates entity for scene
	void CreateEntity(const std::string& argSceneName, std::shared_ptr<Entity>& argEntity, const bool argHasAlpha);

public:
	static World& GetInstance()
	{
		if (world == nullptr) {

			world.reset(new World());

		}
		return *world;
	}

	// Updates world
	void Update();
	// Swaps players (Unposseses if nessercary)
	void SwitchPlayers();

	// Spawns entity in world, returns true if successful
	bool SpawnEntity(const ESpawnableEntities argEntity, const Vector2<float> argPosition, const Vector2<float> argPositionOffset = Vector2<float>(0,0), const ESide argSide = ESide::eNeutral, const Vector2<float>& argSpeed = Vector2<float>(0,0), const float argMaxSpeed = 0, const int argHealth = 0, const int argDamage = 0, Entity** argPlacedEntityRef = nullptr);
	// Spawns a mini-boss
	void SpawnMiniBoss();
	// Spawns the main boss
	void SpawnBoss();

	// Spawns entity in world at location
	void PlaceEntity(const ESpawnableEntities argEnemyType, const Vector2<float> argPosition);
	
	bool LoadScenes();
	// Changes to specified scene
	void ChangeScene(const std::string& argSceneName);
	// Changes to random scene of type
	void ChangeScene(const ESceneType argSceneType);
	// Changes scene to next in type
	void NextScene();

	// Changes world state
	void ChangeWorldState(const EWorldState argState);

	// Resets game variables
	void ResetGame();

	// Increases defeated enemies, if enough have been defeated goto next scene
	void IncreaseDefeatedEnemies();
	// Increases difficulty (Wraps to begining at end)
	void ChangeDifficulty(); 

	// Adds score
	void AddScore(const unsigned int argScore) { score += argScore; };
	// Saves game data to file
	void SaveGameData();
	// Loads game data from file
	void LoadGameData();

	// Returns current score of game
	unsigned int GetScore() const { return score; };
	// Returns current high score of game
	unsigned int GetHighScore() const { return highScore; };

	// Returns current scene
	std::shared_ptr<Scene>& GetScene() { return scenes.at(currentSceneName); };
	// Returns specified scene
	std::shared_ptr<Scene>& GetScene(const std::string& argSceneName) { return scenes.at(argSceneName); };
	// Returns player
	std::shared_ptr<Entity> GetPlayer();
	// Returns Opposing Player
	std::shared_ptr<Entity> GetOpposingPlayer();
	// Returns current scene state
	ESceneState GetSceneState() const { return sceneState; };
	// Returns difficulty
	EDifficulty GetDifficulty() const { return difficulty; };
	// Returns true if a new high score has been achieved
	bool GetHasNewHighScore() { hasNewHighScore = false; return hasNewHighScore; };
};

#define WORLD World::GetInstance()
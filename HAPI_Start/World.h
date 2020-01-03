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

class Renderer;
class Entity;

class World
{
private:
	World();

	static std::shared_ptr<World> world;

	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;

	unsigned short bossesDefeated{ 0 };
	unsigned short requiredDefeatedBosses{ 3 }; /// Number of mini-bosses before final boss


	size_t playerIndex{ 0 };
	size_t vortexIndex{ 0 };

	const int numOfExplosions{ 10 };
	size_t explosionIndex{ 0 };

	const int numOfPlayerProjectiles{ 10 };
	size_t playerProjectilePoolIndex{ 0 };


public:
	float cameraOffset{ 0 }; // TODO Move to private
	std::string currentSceneName{ "Boss_0" }; // TODO Move to Private

	std::shared_ptr<CHapiXML> level; // TODO Temp

	std::shared_ptr<Scene>& GetScene(const std::string& argSceneName) { return scenes.at(argSceneName); };

	static World& GetInstance()
	{
		if (world == nullptr) {

			world.reset(new World());

		}
		return *world;
	}

	void Update();

	void FirePlayerProjectile(const Vector2<float>& argPosition, const Vector2<float>& argSpeed, const ESide argSide, const int argDamage);
	void SpawnExplosion(const Vector2<float>& argPosition);

	void SpawnEntity(const std::string& argRoomName, std::shared_ptr<Entity>& argEntity, const bool argHasAlpha, Vector2<int> argNumOfSpriteCells);
	bool LoadScenes();
	// Changes to specified scene
	void ChangeScene(const std::string& argSceneName);
	// Changes to random scene of type
	void ChangeScene(const ESceneType argSceneType);
	// Changes scene to next in type
	void NextScene();

	std::shared_ptr<Entity>& GetPlayer();
	std::shared_ptr<Entity>& GetVortex();

};

#define WORLD World::GetInstance()
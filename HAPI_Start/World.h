#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

#include <vector>
#include <unordered_map>

/// My Headers
#include "Vector2.h"

class Renderer;
class Entity;

class World
{
private:
	std::shared_ptr<Renderer> window;
	std::unordered_map<std::string, std::shared_ptr<Entity>> entities;



public:
	World(const Vector2<int> argScreenDimensions, const std::string& argScreenName);
	~World();
	void Update();

	void SpawnEntity(const std::string& argName, std::shared_ptr<Entity>& argEntity, const bool argHasAlpha, Vector2<int> argNumOfSpriteCells);
	void DrawEntity(const std::string& argName, const float argInterp);

	bool LoadLevel(const std::string& argLevelName = std::string());
};


#pragma once

#include <vector>

#include "Entity.h"

// Type of scene 
enum class ESceneType
{
	eNone,
	eTransition,
	eBoss,
	eReward,
	eUI
};

class Scene
{
private:
	const std::string sceneName;
	int levelLength{ 0 };
	ESceneType sceneType{ ESceneType::eTransition };
public:
	std::vector<std::shared_ptr<Entity>> entities;
	Scene(const std::string& argSceneName, const int argLevelLength, const ESceneType argSceneType);

	// Creates a entity in scene
	void CreateEntity(std::shared_ptr<Entity>& argEntity, const bool argHasAlpha, const Vector2<unsigned int> argNumOfSpriteCells);
	// Updates entities in scene
	void UpdateScene();
	// Checks collisions against self
	void CheckCollisions();
	// Checks collisions against another scene
	void CheckCollisions(std::shared_ptr<Scene>& argScene);
	
	// Draws all entities in scene
	void DrawScene(const float argInterp, const float argCameraOffset) const;

	// Disables all active entities
	void DisableAllEntities();

	// Returns the level length
	int GetLevelLength() const { return levelLength; };
	// Returns the scene type
	ESceneType GetSceneType() const { return sceneType; };
	// Returns the scene name
	std::string GetSceneName() const { return sceneName; };
};


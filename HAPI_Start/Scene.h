#pragma once

#include <vector>

#include "Entity.h"

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
	std::vector<std::shared_ptr<Entity>> entities; // MOVE TO PRivate
	Scene(const std::string& argSceneName, const int argLevelLength, const ESceneType argSceneType);

	void CreateEntity(std::shared_ptr<Entity>& argEntity, const bool argHasAlpha, const Vector2<unsigned int> argNumOfSpriteCells);
	void UpdateScene();
	// Checks collisions against self
	void CheckCollisions();
	// Checks collisions against another scene
	void CheckCollisions(std::shared_ptr<Scene> argScene);
	void DrawScene(const float argInterp, const float argCameraOffset) const;

	void DisableAllEntities();

	int GetLevelLength() const { return levelLength; };
	ESceneType GetSceneType() const { return sceneType; };
	std::string GetSceneName() const { return sceneName; };
};


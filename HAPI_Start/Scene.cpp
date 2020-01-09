#include "Scene.h"

#include "World.h"
#include "Time.h"
#include "Tile.h"

Scene::Scene(const std::string& argSceneName, const int argLevelLength, const ESceneType argSceneType)
	: sceneName(argSceneName), levelLength(argLevelLength), sceneType(argSceneType)
{
}

void Scene::CreateEntity(std::shared_ptr<Entity>& argEntity, const bool argHasAlpha, const Vector2<unsigned int> argNumOfSpriteCells)
{
	if (argEntity == nullptr)
	{
		std::cerr << "ERROR - Spawning entity but is nullptr, SpawningID=" << entities.size() << std::endl;
		return;
	}

	if (!argEntity->CreateSprite(argHasAlpha, argNumOfSpriteCells))
		std::clog << "ERROR - Spawning entity but failed, SpawningID=" << entities.size() << std::endl;

	/// Adds entity to vector
	entities.push_back(argEntity);
}

void Scene::UpdateScene()
{
	for (std::shared_ptr<Entity> entity : entities)
		if (entity->GetActive())
			entity->Update();
}

void Scene::CheckCollisions()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->GetActive())
		{
			for (size_t j = i + 1; j < entities.size(); j++)
			{
				if (entities[j]->GetActive())
				{
					/// continues if both entities are on the same side
					if (entities[i]->GetSide() == entities[j]->GetSide())
						continue;

					/// continues if any of the entities are neutral
					if (entities[i]->GetSide() == ESide::eNeutral || entities[j]->GetSide() == ESide::eNeutral)
						continue;

					/// Checks collision between entities, if they collide then trigger collision
					if (entities[i]->CheckCollision(*entities[j]))
					{
						entities[i]->Collided(*entities[j]);
						entities[j]->Collided(*entities[i]);

						entities[i]->AfterCollided(*entities[j]);
						entities[j]->AfterCollided(*entities[i]);
					}
				}
			}
		}
	}
}

void Scene::CheckCollisions(std::shared_ptr<Scene>& argScene)
{
	std::vector<std::shared_ptr<Entity>>& otherEntities{ argScene->entities };

	for (std::shared_ptr<Entity> entity : entities)
	{
		if (entity->GetActive())
		{
			for (std::shared_ptr<Entity> otherEntity : otherEntities)
			{
				if (otherEntity->GetActive())
				{
					/// continues if both entities are on the same side
					if (entity->GetSide() == otherEntity->GetSide())
						continue;

					/// continues if any of the entities are neutral
					if (entity->GetSide() == ESide::eNeutral || otherEntity->GetSide() == ESide::eNeutral)
						continue;

					/// Checks collision between entities, if they collide then trigger collision
					if (entity->CheckCollision(*otherEntity))
					{
						entity->Collided(*otherEntity);
						otherEntity->Collided(*entity);

					}
				}
			}
		}
	}
}

void Scene::DrawScene(const float argInterp, const float argCameraOffset) const
{
	for (std::shared_ptr<Entity> entity : entities)
		if (entity->GetActive())
			entity->Draw(argInterp, argCameraOffset);
}

void Scene::DisableAllEntities()
{
	for (std::shared_ptr<Entity> entity : entities)
		if(entity->GetActive())
			entity->SetActive(false);
}

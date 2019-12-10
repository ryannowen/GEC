#include "World.h"

#include "Renderer.h"
#include "Time.h"

#include "Entity.h"
#include "Renderer.h"

#include "Player.h"

std::shared_ptr<World> World::world{ nullptr };

World::World()
{
	RENDERER->CreateWindow(Vector2<int>(1600, 900), "Test");

	LoadLevel();
}

void World::Update()
{
	/// HAPI Update Loop



	while (HAPI.Update())
	{
		TIME->Update();

		/// Checks if enough time has passed to allow for a world tick
		/*if (currentTime - TIME.GetElapsedTimeMiliseconds() > tickLength)
		{
			tick = true;

			/// Updates Delta time and progressess timers
			TIME.Update();
		}*/

		//std::cout << "Time Elapsed = " << Time::GetDeltaTimeMiliseconds() << " Milliseconds" << std::endl;

		/// Clears screen to black
		RENDERER->ClearScreen(HAPI_TColour::BLACK);

		const bool tick{ TIME->GetHasTicked() };
		for (auto& entity : entities)
		{
			if (tick)
			{
				entity.second->Update();



			}


			float interp{ TIME->CalculateInterp() };

			/// Clamps Interpolation between 0 and 1 for scaling purposes
			if (interp > 1)
				interp = 1;
			else if (interp < 0)
				interp = 0;

			DrawEntity(entity.first, interp);
		}

		/// Auto Close for performance tests (seconds * 1000)
		/*if ((time::GetElapsedTime()) > 30000)
		{
			HAPI.Close();
		}*/

		
		//for(int i = 0; i < 200; i++)
		//	window->DrawSprite("Data//alphaThing.tga", Vector2<float>(rand() % 1600, rand() % 900));
	}
}

void World::SpawnEntity(const std::string& argName, std::shared_ptr<Entity>& argEntity, const bool argHasAlpha, const Vector2<int> argNumOfSpriteCells = Vector2<int>(1, 1))
{
	if (entities.find(argName) != entities.end())
	{
		std::cerr << "ERROR - Spawning entity with the same name as another, name=" << argName << std::endl;
		return;
	}

	if (argEntity == nullptr)
	{
		std::cerr << "ERROR - Spawning entity but is nullptr, name=" << argName << std::endl;
		return;
	}

	if (argEntity->CreateSprite(argHasAlpha, argNumOfSpriteCells))
	{
		entities[argName] = argEntity;
	}
	else
		std::cerr << "ERROR - Spawning entity but couldn't create sprite, name=" << argName << std::endl;
	
}

void World::DrawEntity(const std::string& argName, const float argInterp)
{
	if (entities.find(argName) == entities.end())
	{
		std::cerr << "ERROR - Trying to draw entity with incorrect name, name=" << argName << std::endl;
		return;
	}

	entities.at(argName)->Draw(argInterp);
}

bool World::LoadLevel(const std::string& argLevelName)
{
	/*if (argLevelName == std::string())
	{
		std::cerr << "ERROR - Trying to load level but name is incorrect, name=" << argLevelName << std::endl;
		return false;
	}*/

	std::vector<int> keyboardMovementKeys =
	{
		HK_UP,
		HK_DOWN,
		HK_RIGHT,
		HK_LEFT
	};

	std::vector<int> controllerMovementKeys =
	{
		HK_ANALOGUE_LEFT_THUMB_X,
		HK_ANALOGUE_LEFT_THUMB_Y
	};

//	SpawnEntity("background", std::static_pointer_cast<Entity>(std::make_shared<Player>(Vector2<float>(0.0f, 0.0f), "Data//background.tga", std::vector<int>(), std::vector<int>())), false);
	SpawnEntity("player1", std::static_pointer_cast<Entity>(std::make_shared<Player>(Vector2<float>(50.0f, 50.0f), "Data//ArcherSheet.png", keyboardMovementKeys, controllerMovementKeys)), true, Vector2<int>(10, 6));
	
	return true;
}

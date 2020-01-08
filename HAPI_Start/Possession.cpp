#include "Possession.h"

#include "World.h"
#include "Audio.h"

Possession::Possession()
	: Entity(std::string(), AnimationData(Vector2<unsigned int>(0,0), std::vector<float>(), std::vector<unsigned int>(), std::vector<bool>()), Rectangle(32, 0, 32, 0), std::static_pointer_cast<Controller>(std::make_shared<Controller>()))

{
	AUDIO.LoadSound("Data//Sounds//Possession.wav", HAPI_TSoundOptions(1));
}

void Possession::Update()
{
}

void Possession::Collided(Entity& argEntity)
{
	if (argEntity.isPossessable && !argEntity.isPossessed)
	{
		std::shared_ptr<Entity> oppossingPlayer{ WORLD.GetOpposingPlayer() };
		oppossingPlayer->SetActive(false);


		argEntity.SwapControllerInput(oppossingPlayer);
		argEntity.isPossessed = true;
		
		AUDIO.PlaySound("Data//Sounds//Possession.wav");

		SetActive(false);
	}
}

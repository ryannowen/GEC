#include "Possession.h"

#include "World.h"

#include "Player_Opposing.h"

Possession::Possession()
	: Entity(std::string(), AnimationData(Vector2<unsigned int>(0,0), std::vector<float>(), std::vector<unsigned int>(), std::vector<bool>()), Rectangle(32, 0, 32, 0), std::static_pointer_cast<Controller>(std::make_shared<Controller>()))

{
}

void Possession::Update()
{
}

void Possession::Collided(Entity& argEntity)
{
	/// If collided entity is possessable and not possessed then possess the entity
	if (argEntity.isPossessable && !argEntity.isPossessed)
	{
		std::shared_ptr<Player_Opposing> opposingPlayer{ std::static_pointer_cast<Player_Opposing>(WORLD.GetOpposingPlayer()) };
		opposingPlayer->BeginPossessing(argEntity);

		SetActive(false);
	}
}

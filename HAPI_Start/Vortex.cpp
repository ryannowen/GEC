#include "Vortex.h"

#include "World.h"
#include "Audio.h"

bool Vortex::TakeDamage(const Entity& argEntity)
{
	return true;
}

Vortex::Vortex(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller>()))
{
	passable = true;

	AUDIO.LoadSound(teleportSound, HAPI_TSoundOptions(0.25f));
}

void Vortex::Update()
{
}

void Vortex::Collided(Entity& argEntity)
{
	Entity& player{ *WORLD.GetPlayer() };

	/// checks if entity is player
	if (argEntity == player)
	{
		player.SetVelocity(Vector2<float>(0, 0));
		player.SetAcceleration(Vector2<float>(0, 0));

		AUDIO.PlaySound(teleportSound);
		WORLD.NextScene();

		SetActive(false);
	}
}

#include "TriggerBox.h"

#include "World.h"

bool TriggerBox::TakeDamage(const Entity& argEntity)
{
	return true;
}

TriggerBox::TriggerBox(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle& argCollisionBounds)
	: Entity(argSpritePath, argAnimData, argCollisionBounds, std::shared_ptr<Controller>(std::make_shared<Controller>()))
{
}

void TriggerBox::Update()
{
}

void TriggerBox::Collided(Entity& argEntity)
{
	Entity& player{ *WORLD.GetPlayer() };

	/// checks if entity is player
	if (static_cast<int>(argEntity.currentPosition.x) == static_cast<int>(player.currentPosition.x)
		&& static_cast<int>(argEntity.currentPosition.y) == static_cast<int>(player.currentPosition.y))
	{
		player.currentPosition = Vector2<float>(200, 730);
		player.SetVelocity(Vector2<float>(0, 0));
		WORLD.NextScene();
		SetActive(false);
	}
}

#include "Explosion.h"
#include "Audio.h"

void Explosion::OnAnimFinished()
{
	SetActive(false);
}

void Explosion::OnEnable()
{
	AUDIO.PlaySound(sound);
}

Explosion::Explosion(const std::string& argSpritePath, const AnimationData& argAnimData, const Rectangle argCollision)
	: Entity(argSpritePath, argAnimData, argCollision, std::shared_ptr<Controller>(std::make_shared<Controller>()))
{
	AUDIO.LoadSound(sound, HAPI_TSoundOptions(1));

	passable = true;
}

void Explosion::Update()
{
}

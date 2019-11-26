#include "Entity.h"

#include "Renderer.h"
#include "Time.h"

Entity::Entity(Vector2<float> argPosition, std::string argSpritePath)
	: currentPosition(argPosition), oldPosition(argPosition), spritePath(argSpritePath)
{
}

void Entity::Translate(Vector2<float> argPosition)
{
	/// Updates old position for interpolation to be accurate and correct, then updates main position
	oldPosition = currentPosition;
	currentPosition += argPosition;
}

bool Entity::CreateSprite(std::shared_ptr<Renderer>& argRenderer, const bool argHasAlpha, const Vector2<int> argNumOfSpriteCells)
{
	return argRenderer->CreateSprite(spritePath, argHasAlpha, argNumOfSpriteCells);
}

void Entity::Draw(std::shared_ptr<Renderer>& argRenderer, const float argInterp)
{
	//currentSpriteCells.x++;

	/// Calculates interpolation to smoothly draw between the old and new position
	Vector2<float> newPosition{ oldPosition + ((currentPosition - oldPosition) * argInterp) };
	argRenderer->DrawSprite(spritePath, newPosition, currentSpriteCells);


}
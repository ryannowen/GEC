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

bool Entity::CreateSprite(const bool argHasAlpha, const Vector2<int> argNumOfSpriteCells)
{
	return RENDERER->CreateSprite(spritePath, argHasAlpha, argNumOfSpriteCells);
}

void Entity::Draw(const float argInterp)
{
	//currentSpriteCells.x++;

	/// Calculates interpolation to smoothly draw between the old and new position
	Vector2<float> newPosition{ oldPosition + ((currentPosition - oldPosition) * argInterp) };
	RENDERER->DrawSprite(spritePath, newPosition, currentSpriteCells);


}
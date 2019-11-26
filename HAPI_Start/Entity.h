#pragma once

#include <iostream>

/// My Headers
#include "Vector2.h"

class Renderer;

class Entity
{
protected:
	Vector2<float> oldPosition{ 0.0f, 0.0f };
	Vector2<float> currentPosition{ 0.0f, 0.0f };
	std::string spritePath;

	float currentSpriteTimeSeconds{ 0 };
	float currentSpriteSpeedSeconds{ 12.5f };
	Vector2<int> currentSpriteCells{ 1, 1 };

	void Translate(Vector2<float> argPosition);

public:
	Entity(Vector2<float> argPosition, std::string argTexturePath);
	virtual void Update() = 0;

	bool CreateSprite(std::shared_ptr<Renderer>& argRenderer, bool argHasAlpha, Vector2<int> argNumOfSpriteCells);
	void Draw(std::shared_ptr<Renderer>& argRenderer, const float argInterp);
};


#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

// My Headers
#include "Vector2.h"
#include "Rectangle.h"

class Sprite
{
private:
	BYTE* texturePtr{ nullptr };
	Vector2<int> spriteDimensions{ 0,0 };
	Rectangle spriteBounds;
	bool hasAlpha;

	Vector2<int> numOfCells{ 0, 0 };

	bool FastBlit(BYTE* argScreenPointer, Rectangle& argScreen, Vector2<float> argPosition);
	bool AlphaBlit(BYTE* argScreenPointer, Rectangle& argScreen, Vector2<float> argPosition);

public:
	Sprite(const std::string& argSpritePath, const bool argHasAlpha, const Vector2<int> argNumOfSpriteCells);
	~Sprite();
	bool LoadTexture(const std::string& argSpritePath, const bool argHasAlpha = false);
	bool DrawSprite(BYTE* argScreenPointer, Rectangle& argScreen, Vector2<float> argPosition, Vector2<int>& argCurrentCells);
};


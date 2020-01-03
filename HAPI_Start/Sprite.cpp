#include "Sprite.h"

bool Sprite::FastBlit(BYTE* argScreenPointer, const Rectangle& argScreen, const Vector2<float> argPosition)
{
	BYTE* texturePointer = texturePtr;

	/// Adds offsets
	argScreenPointer += (static_cast<size_t>(argPosition.y) * argScreen.Width() + static_cast<int>(argPosition.x)) * 4;
	texturePointer += (static_cast<size_t>(spriteBounds.top) * spriteDimensions.x + static_cast<int>(spriteBounds.left)) * 4;

	const int boundsHeight{ spriteBounds.Height() };

	///Draws Texture
	for (int i = 0; i < boundsHeight; i++)
	{
		memcpy(argScreenPointer, texturePointer, static_cast<size_t>(spriteBounds.Width()) * 4);

		/// Applies Offsets
		argScreenPointer += (static_cast<size_t>(argScreen.Width() )) * 4;
		texturePointer += (static_cast<size_t>(spriteDimensions.x) ) * 4;
	}

	return true;
}

bool Sprite::AlphaBlit(BYTE* argScreenPointer, const Rectangle& argScreen, const Vector2<float> argPosition)
{
	BYTE* texturePointer = texturePtr;

	/// Adds offsets
	argScreenPointer += (static_cast<size_t>(argPosition.y) * argScreen.Width() + static_cast<int>(argPosition.x)) * 4;
	texturePointer += (static_cast<size_t>(spriteBounds.top) * spriteDimensions.x + static_cast<int>(spriteBounds.left)) * 4;

	int alpha{ 0 };
	const int screenNextLineOffset{ (argScreen.Width() - spriteBounds.Width()) * 4 };
	const int textureNextLineOffset{ (spriteDimensions.x - spriteBounds.Width()) * 4 };

	const int boundsHeight{ spriteBounds.Height() };
	const int boundsWidth{ spriteBounds.Width() };

	for (int y = 0; y < boundsHeight; y++)
	{
		for (int x = 0; x < boundsWidth; x++)
		{
			if (texturePointer[3] == 255) /// Full alpha = Copy full pixel
				memcpy(argScreenPointer, texturePointer, 4);
			else if (texturePointer[3] != 0) /// Not full alpha = Blend between screen and pixel
			{
				alpha = texturePointer[3];

				argScreenPointer[0] += ((alpha * (texturePointer[0] - argScreenPointer[0])) >> 8);
				argScreenPointer[1] += ((alpha * (texturePointer[1] - argScreenPointer[1])) >> 8);
				argScreenPointer[2] += ((alpha * (texturePointer[2] - argScreenPointer[2])) >> 8);
			}

			/// Offsets more to be in correct X position
			texturePointer += 4;
			argScreenPointer += 4;
		}

		/// Offsets to next line below
		texturePointer += textureNextLineOffset;
		argScreenPointer += screenNextLineOffset;
	}

	return true;
}

Sprite::Sprite(const std::string& argSpritePath, const bool argHasAlpha, const Vector2<int> argTotalNumOfSpriteCells)
	: hasAlpha(argHasAlpha), totalNumOfCells(argTotalNumOfSpriteCells)
{
	if (argSpritePath != "")
		LoadTexture(argSpritePath, hasAlpha);
}

Sprite::~Sprite()
{
	delete[] texturePtr;
}

/// Returns true if texture loaded correctly and updates texture dimensions, otherwise false 
bool Sprite::LoadTexture(const std::string& argSpritePath, const bool argHasAlpha)
{
	if (texturePtr != nullptr)
		delete[] texturePtr;

	if (!HAPI.LoadTexture(argSpritePath, &texturePtr, spriteDimensions.x, spriteDimensions.y))
	{
		std::cerr << "ERROR: Loading Texture failed, Inputted file Name=" << argSpritePath << std::endl;
		return false;
	}

	hasAlpha = argHasAlpha;

	return true;
}

bool Sprite::DrawSprite(BYTE* argScreenPointer, const Rectangle& argScreen, Vector2<float> argPosition, Vector2<unsigned int>& argCurrentCells)
{
	if (texturePtr == nullptr)
		return false;

	/// Updates Bounds to sprite cell size
	spriteBounds.UpdateDimensions(spriteDimensions.x / totalNumOfCells.x, spriteDimensions.y / totalNumOfCells.y);

	/// Calculates cell location on spritesheet for translating when drawing (Required before clipping)
	int CellLocX{ spriteBounds.right * (static_cast<int>(argCurrentCells.x)) }, CellLocY{ spriteBounds.bottom * (static_cast<int>(argCurrentCells.y)) };

	/// Translates Sprite into Screen Space
	spriteBounds.Translate(static_cast<int>(argPosition.x), static_cast<int>(argPosition.y));

	/// Checks if sprite is completely out of the screen
	if (spriteBounds.CompletelyOutside(argScreen))
		return false;

	/// Checks if sprite is comletely on the screen, if not clip the bounds
	if (!spriteBounds.CompletelyContains(argScreen))
		spriteBounds.ClipTo(argScreen);

	/// Translates back to sprite space
	spriteBounds.Translate(static_cast<int>(-argPosition.x), static_cast<int>(-argPosition.y));

	/// Clamps to screen
	if (argPosition.x < 0)
	{
		argPosition.x = 0;
	}
	if (argPosition.y < 0)
	{
		argPosition.y = 0;
	}

	/// Translates into correct cell location for sprite
	spriteBounds.Translate(CellLocX, CellLocY);

	/// Begins blitting depending on sprite alpha
	bool blitSuccesss{ false };
	if (hasAlpha)
		blitSuccesss = AlphaBlit(argScreenPointer, argScreen, argPosition);
	else
		blitSuccesss = FastBlit(argScreenPointer, argScreen, argPosition);

	/// Translates back to start of sprite
	spriteBounds.Translate(-CellLocX, -CellLocY);


	return blitSuccesss;
}



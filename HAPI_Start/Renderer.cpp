#include "Renderer.h"

#include "Sprite.h"

std::shared_ptr<Renderer> Renderer::renderer{ nullptr };

Renderer::Renderer()
{

}

void Renderer::CreateWindow(Vector2<int> argScreenDimensions, const std::string& argWindowName)
{
	/// Creates Screen
	if (!HAPI.Initialise(argScreenDimensions.x, argScreenDimensions.y, argWindowName))
		return;

	/// Updates screen dimensions and bounds
	screenDimensions = argScreenDimensions;
	screenBounds.UpdateDimensions(screenDimensions.x, screenDimensions.y);

	/// Gets screen pointer for drawing
	screenPointer = HAPI.GetScreenPointer();
}

bool Renderer::CreateSprite(const std::string& argSpritePath, const bool argHasAlpha, const Vector2<unsigned int> argNumOfSpriteCells)
{
	if (argSpritePath == "")
		return false;
	
	/// Checks if space is available in map for sprite, and creates sprite if there is
	if (spriteMap.find(argSpritePath) == spriteMap.end())
	{
		spriteMap[argSpritePath] = std::make_shared<Sprite>(argSpritePath, argHasAlpha, argNumOfSpriteCells);
		return true;
	}

	return false;
}

void Renderer::ClearScreen(const HAPI_TColour argScreenColour)
{
	/// Clears Screen to Colour
	if (((argScreenColour.red == argScreenColour.green) && (argScreenColour.green == argScreenColour.blue)))
	{
		std::fill(screenPointer, screenPointer + (static_cast<size_t>(screenDimensions.x) * screenDimensions.y * 4), argScreenColour.red);
	}
	else
	{
		/// Sets First Pixel to screen colour
		memcpy(screenPointer, &argScreenColour, 4);

		int bytes{ 4 };
		bool completed{ false };
		const int halfScreenBytes{ (screenDimensions.x * screenDimensions.y * 2) };

		while (!completed)
		{
			if (bytes >= halfScreenBytes)
			{
				completed = true;
				bytes = halfScreenBytes;
			}

			/// Duplicates number of coloured pixels
			std::copy(screenPointer, screenPointer + bytes, screenPointer + bytes);

			bytes *= 2;
		}
	}

}

void Renderer::DrawSprite(const std::string& argSpritePath, const Vector2<float> argPosition, Vector2<unsigned int>& argCurrentCells)
{
	if (screenPointer == nullptr)
	{
		std::cerr << "ERROR: Trying to draw sprite, ScreenPointer is nullptr" << std::endl;
		return;
	}

	/// Checks if sprite has been created in map
	if (spriteMap.find(argSpritePath) != spriteMap.end())
	{
		std::shared_ptr<Sprite>& sprite{ spriteMap.at(argSpritePath) };
		if (sprite == nullptr)
		{
			std::cerr << "ERROR: Trying to draw sprite, but is nullptr" << std::endl;
			return;
		}

		spriteMap.at(argSpritePath)->DrawSprite(screenPointer, screenBounds, argPosition, argCurrentCells);
	}
}



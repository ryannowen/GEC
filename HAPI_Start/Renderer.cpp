#include "Renderer.h"

#include "Sprite.h"

std::shared_ptr<Renderer> Renderer::renderer{ nullptr };

Renderer::Renderer()
{

}

void Renderer::CreateWindow(const Vector2<int> argScreenDimensions, const std::string& argWindowName)
{
	int w{ 1600 }, h{ 900 };

	if (!HAPI.Initialise(w, h, "Test")) return;

	screenDimensions = argScreenDimensions;

	screenPointer = HAPI.GetScreenPointer();
	screenBounds.UpdateDimensions(screenDimensions.x, screenDimensions.y);
}

bool Renderer::CreateSprite(const std::string& argSpritePath, const bool argHasAlpha, const Vector2<int> argNumOfSpriteCells)
{
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

void Renderer::DrawSprite(const std::string& argSpritePath, const Vector2<float> argPosition, Vector2<int>& argCurrentCells)
{
	if (screenPointer == nullptr)
	{
		std::cerr << "ERROR: Trying to draw sprite, ScreenPointer is nullptr" << std::endl;
		return;
	}

	if (spriteMap.find(argSpritePath) != spriteMap.end())
	{
		std::shared_ptr<Sprite> sprite{ spriteMap.at(argSpritePath) };
		if (sprite == nullptr)
		{
			std::cerr << "ERROR: Trying to draw sprite, but is nullptr" << std::endl;
			return;
		}

		spriteMap.at(argSpritePath)->DrawSprite(screenPointer, screenBounds, argPosition, argCurrentCells);
	}
}



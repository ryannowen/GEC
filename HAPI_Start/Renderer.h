#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

#include <unordered_map>

/// My Headers
#include "Rectangle.h"
#include "Vector2.h"

class Sprite;

class Renderer
{
private:
	Renderer();

	static std::shared_ptr<Renderer> renderer;
	
	// Screen area
	Rectangle screenBounds;
	Vector2<int> screenDimensions{ Vector2<int>(1600, 900) };

	// Ptr to screen first pixel
	BYTE* screenPointer{ nullptr };

	std::unordered_map<std::string, std::shared_ptr<Sprite>> spriteMap;
public:
	static Renderer& GetInstance()
	{
		if (!renderer)
		{
			renderer.reset(new Renderer());
		}

		return *renderer;
	}

	// Creates Window for renderering
	void CreateWindow(Vector2<int> argScreenDimensions = Vector2<int>(1600, 900), const std::string& argWindowName = "Unknown Name");

	// Creates sprite for renderering
	bool CreateSprite(const std::string& argSpritePath, const bool argHasAlpha, const Vector2<unsigned int> argNumOfSpriteCells);

	// Clears screen to colour
	void ClearScreen(const HAPI_TColour argColour);

	// Draws sprite to screen window
	void DrawSprite(const std::string& argSpritePath, const Vector2<float> argPosition, Vector2<unsigned int>& argCurrentCells);
};

#define RENDERER Renderer::GetInstance()


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

	Rectangle screenBounds;
	Vector2<int> screenDimensions{ Vector2<int>(1600, 900) };

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

	void CreateWindow(Vector2<int> argScreenDimensions = Vector2<int>(1600, 900), const std::string& argWindowName = "Unknown Name");

	bool CreateSprite(const std::string& argSpritePath, const bool argHasAlpha, Vector2<int> argNumOfSpriteCells);

	void ClearScreen(const HAPI_TColour argColour);
	void DrawSprite(const std::string& argSpritePath, const Vector2<float> argPosition, Vector2<unsigned int>& argCurrentCells);
};

#define RENDERER Renderer::GetInstance()


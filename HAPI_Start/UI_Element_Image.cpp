#include "UI_Element_Image.h"

#include "Renderer.h"
#include "UI_Window.h"

UI_Element_Image::UI_Element_Image(const Vector2<float> argPosition, const std::string& argSpritePath, const bool argHasAlpha, const Vector2<unsigned int> argTotalCells, const Vector2<unsigned int> argCurrentCells)
	: UI_Element(argPosition), spritePath(argSpritePath), currentCells(argCurrentCells)
{
	RENDERER.CreateSprite(spritePath, argHasAlpha, argTotalCells);
}

void UI_Element_Image::UpdateElement(UI_Window& argWindow)
{
}

void UI_Element_Image::DrawElement(const UI_Window& argWindow)
{
	RENDERER.DrawSprite(spritePath, position + argWindow.position, currentCells);
}

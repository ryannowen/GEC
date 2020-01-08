#include "UI_Text.h"

#include "UI_Window.h"


UI_Text::UI_Text(const Vector2<float> argPosition, const HAPI_TColour argColour, const std::string& argText, const int argSize, const std::string& argFontPath)
	: UI_Element(argPosition), colour(argColour), text(argText), size(argSize), fontPath(argFontPath)
{
}

void UI_Text::UpdateElement(UI_Window& argWindow)
{
}

void UI_Text::DrawElement(const UI_Window& argWindow)
{
	if (fontPath != std::string())
		HAPI.ChangeFontFromFile(fontPath);

	HAPI.RenderText(position.x + argWindow.position.x, position.y + argWindow.position.y, colour, text, size);
}

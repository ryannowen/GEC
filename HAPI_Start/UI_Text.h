#pragma once
#include "UI_Element.h"

#include <string>

class UI_Text :public UI_Element
{
private:
	friend class UI_Window;

	std::string text;
	int size;
	HAPI_TColour colour;
	std::string fontPath;
public:
	UI_Text(const Vector2<float> argPosition, const HAPI_TColour argColour, const std::string& argText, const int argSize, const std::string& argFontPath);

	virtual void UpdateElement(UI_Window& argWindow) override final;

	// Draws text element to screen
	virtual void DrawElement(const UI_Window& argWindow) override final;

	// Changes text
	void SetText(const std::string& argText) { text = argText; };

};


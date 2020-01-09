#pragma once
#include "UI_Element.h"

class UI_Element_Image : public UI_Element
{
private:
	std::string spritePath;
	Vector2<unsigned int> currentCells;
public:
	UI_Element_Image(const Vector2<float> argPosition, const std::string& argSpritePath, const bool argHasAlpha, const Vector2<unsigned int> argTotalCells, const Vector2<unsigned int> argCurrentCells);

	virtual void UpdateElement(UI_Window& argWindow) override final;

	// Draws image sprite
	virtual void DrawElement(const UI_Window& argWindow) override final;

	// Changes image sprite current cells for renderering
	void SetCurrentCells(Vector2<unsigned int> argCurrentCells) { currentCells = argCurrentCells; };
};


#pragma once

#include "UI_Button.h"

class UI_Button_ChangeDifficulty : public UI_Button
{
protected:
	// When mouse begins hovering
	virtual void OnBeginHover(UI_Window& argWindow) override final;
	// When mouse ends hovering
	virtual void OnEndHover(UI_Window& argWindow) override final;
	// When mouse starts clicking
	virtual void OnBeginClick(UI_Window& argWindow) override final;
	// When mouse ends clicking
	virtual void OnEndClick(UI_Window& argWindow) override final;

public:
	UI_Button_ChangeDifficulty(const Vector2<float> argButtonPosition = Vector2<float>(0, 0), const Vector2<float> argButtonCollision = Vector2<float>(20, 20), const Vector2<float> argTextPosition = Vector2<float>(0, 0), const HAPI_TColour argTextColour = HAPI_TColour::RED, const std::string& argText = "No Inputed Label Text", const int argTextSize = 10, const std::string & argFontPath = std::string(), const std::string & argButtonSprite = std::string(), const std::string & argHoverSoundPath = std::string(), const HAPI_TSoundOptions & argHoverSoundOptions = HAPI_TSoundOptions(), const std::string & argPressedSoundPath = std::string(), const HAPI_TSoundOptions & argPressedSoundOptions = HAPI_TSoundOptions());
};


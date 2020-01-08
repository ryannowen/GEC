#include "UI_Button_Resume.h"

#include "World.h"

void UI_Button_Resume::OnBeginHover(UI_Window& argWindow)
{
}

void UI_Button_Resume::OnEndHover(UI_Window& argWindow)
{
}

void UI_Button_Resume::OnBeginClick(UI_Window& argWindow)
{
}

void UI_Button_Resume::OnEndClick(UI_Window& argWindow)
{
	WORLD.ChangeWorldState(EWorldState::eInGame);
}

UI_Button_Resume::UI_Button_Resume(const Vector2<float> argButtonPosition, const Vector2<float> argButtonCollision, const Vector2<float> argTextPosition, const HAPI_TColour argTextColour, const std::string& argText, const int argTextSize, const std::string& argFontPath, const std::string& argButtonSprite, const std::string& argHoverSoundPath, const HAPI_TSoundOptions& argHoverSoundOptions, const std::string& argPressedSoundPath, const HAPI_TSoundOptions& argPressedSoundOptions)
	: UI_Button(argButtonPosition, argButtonCollision, argTextPosition, argTextColour, argText, argTextSize, argFontPath, argButtonSprite, argHoverSoundPath, argHoverSoundOptions, argPressedSoundPath, argPressedSoundOptions)

{
}

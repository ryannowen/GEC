#include "UI_Button_ChangeDifficulty.h"

#include "World.h"

void UI_Button_ChangeDifficulty::OnBeginHover(UI_Window& argWindow)
{
}

void UI_Button_ChangeDifficulty::OnEndHover(UI_Window& argWindow)
{
}

void UI_Button_ChangeDifficulty::OnBeginClick(UI_Window& argWindow)
{
}

void UI_Button_ChangeDifficulty::OnEndClick(UI_Window& argWindow)
{
	WORLD.ChangeDifficulty();
}

UI_Button_ChangeDifficulty::UI_Button_ChangeDifficulty(const Vector2<float> argButtonPosition, const Vector2<float> argButtonCollision, const Vector2<float> argTextPosition, const HAPI_TColour argTextColour, const std::string& argText, const int argTextSize, const std::string& argFontPath, const std::string& argButtonSprite, const std::string& argHoverSoundPath, const HAPI_TSoundOptions& argHoverSoundOptions, const std::string& argPressedSoundPath, const HAPI_TSoundOptions& argPressedSoundOptions)
	: UI_Button(argButtonPosition, argButtonCollision, argTextPosition, argTextColour, argText, argTextSize, argFontPath, argButtonSprite, argHoverSoundPath, argHoverSoundOptions, argPressedSoundPath, argPressedSoundOptions)

{
}

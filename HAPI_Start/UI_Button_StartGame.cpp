#include "UI_Button_StartGame.h"

#include "World.h"

void UI_Button_StartGame::OnBeginHover(UI_Window& argWindow)
{
}

void UI_Button_StartGame::OnEndHover(UI_Window& argWindow)
{
}

void UI_Button_StartGame::OnBeginClick(UI_Window& argWindow)
{
}

void UI_Button_StartGame::OnEndClick(UI_Window& argWindow)
{
	WORLD.ResetGame();
	WORLD.NextScene();
}

UI_Button_StartGame::UI_Button_StartGame(const Vector2<float> argButtonPosition, const Vector2<float> argButtonCollision, const Vector2<float> argTextPosition, const HAPI_TColour argTextColour, const std::string& argText, const int argTextSize, const std::string& argFontPath, const std::string& argButtonSprite, const std::string& argHoverSoundPath, const HAPI_TSoundOptions& argHoverSoundOptions, const std::string& argPressedSoundPath, const HAPI_TSoundOptions& argPressedSoundOptions)
	: UI_Button(argButtonPosition, argButtonCollision, argTextPosition, argTextColour, argText, argTextSize, argFontPath, argButtonSprite, argHoverSoundPath, argHoverSoundOptions, argPressedSoundPath, argPressedSoundOptions)

{
}

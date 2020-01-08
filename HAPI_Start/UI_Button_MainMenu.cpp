#include "UI_Button_MainMenu.h"

#include "UI_Interface.h"
#include "World.h"

void UI_Button_MainMenu::OnBeginHover(UI_Window& argWindow)
{
	
}

void UI_Button_MainMenu::OnEndHover(UI_Window& argWindow)
{

}

void UI_Button_MainMenu::OnBeginClick(UI_Window& argWindow)
{

}

void UI_Button_MainMenu::OnEndClick(UI_Window& argWindow)
{
	WORLD.GetScene("Global")->DisableAllEntities();
	WORLD.ChangeWorldState(EWorldState::eMainMenu);
	WORLD.ChangeScene(ESceneType::eUI);
}

UI_Button_MainMenu::UI_Button_MainMenu(const Vector2<float> argButtonPosition, const Vector2<float> argButtonCollision, const Vector2<float> argTextPosition, const HAPI_TColour argTextColour, const std::string& argText, const int argTextSize, const std::string& argFontPath, const std::string& argButtonSprite, const std::string& argHoverSoundPath, const HAPI_TSoundOptions& argHoverSoundOptions, const std::string& argPressedSoundPath, const HAPI_TSoundOptions& argPressedSoundOptions)
	:	UI_Button(argButtonPosition, argButtonCollision, argTextPosition, argTextColour, argText, argTextSize, argFontPath, argButtonSprite, argHoverSoundPath, argHoverSoundOptions, argPressedSoundPath, argPressedSoundOptions)
{
}


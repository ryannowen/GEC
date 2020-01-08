#include "UI_Window_MainMenu.h"

#include "UI_Button_StartGame.h"
#include "UI_Button_ScoreScreen.h"
#include "UI_Button_Quit.h"

UI_Window_MainMenu::UI_Window_MainMenu(const Vector2<float> argPosition)
	:	UI_Window(argPosition)
{
	Init();
}

void UI_Window_MainMenu::Init()
{
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_StartGame>(Vector2<float>(64, 64), Vector2<float>(256, 128), Vector2<float>(60, 40), HAPI_TColour::BLACK, "Start Game", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_ScoreScreen>(Vector2<float>(64, 192), Vector2<float>(256, 128), Vector2<float>(50, 40), HAPI_TColour::BLACK, "Score Screen", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_Quit>(Vector2<float>(64, 320), Vector2<float>(256, 128), Vector2<float>(95, 40), HAPI_TColour::BLACK, "Quit", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
}

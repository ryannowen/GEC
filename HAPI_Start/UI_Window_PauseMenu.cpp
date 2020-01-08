#include "UI_Window_PauseMenu.h"

#include "UI_Button_MainMenu.h"
#include "UI_Button_Quit.h"
#include "UI_Button_Resume.h"


UI_Window_PauseMenu::UI_Window_PauseMenu(const Vector2<float> argPosition)
	:	UI_Window(argPosition)
{
	Init();
}

void UI_Window_PauseMenu::Init()
{
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(600, 50), HAPI_TColour::BLUE, "Possession", 140, "Data//font_pixel.ttf")));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_Resume>(Vector2<float>(64, 64), Vector2<float>(256, 128), Vector2<float>(80, 40), HAPI_TColour::BLACK, "Resume", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_MainMenu>(Vector2<float>(64, 192), Vector2<float>(256, 128), Vector2<float>(65, 40), HAPI_TColour::BLACK, "Main Menu", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_Quit>(Vector2<float>(64, 320), Vector2<float>(256, 128), Vector2<float>(100, 40), HAPI_TColour::BLACK, "Quit", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));

}

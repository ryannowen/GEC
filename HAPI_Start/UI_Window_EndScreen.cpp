#include "UI_Window_EndScreen.h"

#include "World.h"

#include "UI_Button_MainMenu.h"
#include "UI_Button_ScoreScreen.h"
#include "UI_Button_Quit.h"

void UI_Window_EndScreen::OnEnable()
{
	std::string winningPlayer;

	if (WORLD.GetPlayer()->GetSpritePath() == "Data//Player1.png")
		winningPlayer = "Player 1";
	else
		winningPlayer = "Player 2";

	std::static_pointer_cast<UI_Text>(elements[0])->SetText("Winning Player: " + winningPlayer);
}

UI_Window_EndScreen::UI_Window_EndScreen(const Vector2<float> argPosition)
	: UI_Window(argPosition)
{
	Init();
}

void UI_Window_EndScreen::Init()
{
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(400, 50), HAPI_TColour::BLUE, "Winning Player", 90, "Data//font_pixel.ttf")));

	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_MainMenu>(Vector2<float>(64, 64), Vector2<float>(256, 128), Vector2<float>(65, 40), HAPI_TColour::BLACK, "Main Menu", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_ScoreScreen>(Vector2<float>(64, 192), Vector2<float>(256, 128), Vector2<float>(50, 40), HAPI_TColour::BLACK, "Score Screen", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_Quit>(Vector2<float>(64, 320), Vector2<float>(256, 128), Vector2<float>(100, 40), HAPI_TColour::BLACK, "Quit", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));

}

#include "UI_Window_MainMenu.h"

#include "World.h"


#include "UI_Button_StartGame.h"
#include "UI_Button_ScoreScreen.h"
#include "UI_Button_Quit.h"
#include "UI_Button_ChangeDifficulty.h"

UI_Window_MainMenu::UI_Window_MainMenu(const Vector2<float> argPosition)
	:	UI_Window(argPosition)
{
	Init();
}

void UI_Window_MainMenu::Init()
{
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_ChangeDifficulty>(Vector2<float>(320, 64), Vector2<float>(256, 128), Vector2<float>(30, 40), HAPI_TColour::BLACK, "Change Difficulty", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(350, 144), HAPI_TColour::RED, "Difficulty", 25, "Data//font_pixel.ttf")));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_StartGame>(Vector2<float>(64, 64), Vector2<float>(256, 128), Vector2<float>(60, 40), HAPI_TColour::BLACK, "Start Game", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_ScoreScreen>(Vector2<float>(64, 192), Vector2<float>(256, 128), Vector2<float>(50, 40), HAPI_TColour::BLACK, "Score Screen", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_Quit>(Vector2<float>(64, 320), Vector2<float>(256, 128), Vector2<float>(95, 40), HAPI_TColour::BLACK, "Quit", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
}

void UI_Window_MainMenu::UpdateWindow()
{
	std::string currentDifficulty{ "Unknown" };

	switch (WORLD.GetDifficulty())
	{
	case EDifficulty::eEasy:
		currentDifficulty = "Easy";
		break;

	case EDifficulty::eNormal:
		currentDifficulty = "Normal";
		break;

	case EDifficulty::eHard:
		currentDifficulty = "Hard";
		break;

	case EDifficulty::eInsane:
		currentDifficulty = "INSANE";
		break;
	default:
		currentDifficulty = "Unknown";
		std::cerr << "ERROR: Trying to get difficulty but case isn't specified" << std::endl;
		break;
	}

	std::static_pointer_cast<UI_Text>(elements[1])->SetText("Difficulty: " + currentDifficulty);

	for (std::shared_ptr<UI_Element> element : elements)
	{
		if (element->GetActive())
			element->UpdateElement(*this);
	}

}

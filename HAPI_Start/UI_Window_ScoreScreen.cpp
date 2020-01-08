#include "UI_Window_ScoreScreen.h"

#include "World.h"
#include "UI_Button_MainMenu.h"
#include "UI_Button_Quit.h"
#include "UI_Text.h"
#include "UI_Element_Image.h"

void UI_Window_ScoreScreen::OnEnabled()
{
	std::static_pointer_cast<UI_Text>(elements[1])->SetText("High Score: " + std::to_string(WORLD.GetHighScore()));
	std::static_pointer_cast<UI_Text>(elements[2])->SetText("Score: " + std::to_string(WORLD.GetScore()));

	if (WORLD.GetScore() > WORLD.GetHighScore())
	{
		elements[3]->SetActive(true);
	}
	else
		elements[3]->SetActive(false);
}

UI_Window_ScoreScreen::UI_Window_ScoreScreen(const Vector2<float> argPosition)
	: UI_Window(argPosition)
{
	Init();
}

void UI_Window_ScoreScreen::Init()
{
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Element_Image>(Vector2<float>(384, 64), "Data//Pannel.png", false, Vector2<unsigned int>(1, 1), Vector2<unsigned int>(0, 0))));

	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(480, 170), HAPI_TColour::BLACK, "High: Score", 35, "Data//font_pixel.ttf")));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(480, 200), HAPI_TColour::BLACK, "Score", 35, "Data//font_pixel.ttf")));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(480, 270), HAPI_TColour::RED, "New High Score", 45, "Data//font_pixel.ttf")));

	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(480, 100), HAPI_TColour::BLACK, "Score Screen", 45, "Data//font_pixel.ttf")));


	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_MainMenu>(Vector2<float>(64, 64), Vector2<float>(256, 128), Vector2<float>(65, 40), HAPI_TColour::BLACK, "Main Menu", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_Quit>(Vector2<float>(64, 192), Vector2<float>(256, 128), Vector2<float>(100, 40), HAPI_TColour::BLACK, "Quit", 35, "Data//font_pixel.ttf", "Data//Button.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//Button_Click.wav", HAPI_TSoundOptions(1))));
}

void UI_Window_ScoreScreen::UpdateWindow()
{
	

	for (std::shared_ptr<UI_Element> element : elements)
	{
		if (element->GetActive())
			element->UpdateElement(*this);
	}
}

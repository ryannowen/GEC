#include "UI_Window_Reward.h"

#include "UI_Button_Reward.h"

void UI_Window_Reward::OnEnabled()
{
	std::static_pointer_cast<UI_Button_Reward>(elements[0])->ChangeReward();
	std::static_pointer_cast<UI_Button_Reward>(elements[1])->ChangeReward();
	std::static_pointer_cast<UI_Button_Reward>(elements[2])->ChangeReward();
}

UI_Window_Reward::UI_Window_Reward(const Vector2<float> argPosition)
	: UI_Window(argPosition)
{
	Init();
}

void UI_Window_Reward::Init()
{
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_Reward>(Vector2<float>(352, 128), Vector2<float>(192, 192), Vector2<float>(30, 130), HAPI_TColour::BLACK, "Reward 1", 25, "Data//font_pixel.ttf", "Data//Pannel_Reward.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//ChosenReward.wav", HAPI_TSoundOptions(1), Vector2<float>(33, 20), "Data//Rewards.png", true, Vector2<unsigned int>(3, 1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_Reward>(Vector2<float>(704, 64), Vector2<float>(192, 192), Vector2<float>(30, 130), HAPI_TColour::BLACK, "Reward 2", 25, "Data//font_pixel.ttf", "Data//Pannel_Reward.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//ChosenReward.wav", HAPI_TSoundOptions(1), Vector2<float>(33, 20), "Data//Rewards.png", true, Vector2<unsigned int>(3, 1))));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Button_Reward>(Vector2<float>(1056, 128), Vector2<float>(192, 192), Vector2<float>(30, 130), HAPI_TColour::BLACK, "Reward 3", 25, "Data//font_pixel.ttf", "Data//Pannel_Reward.png", "Data//Sounds//Button_Hover.wav", HAPI_TSoundOptions(1), "Data//Sounds//ChosenReward.wav", HAPI_TSoundOptions(1), Vector2<float>(33, 20), "Data//Rewards.png", true, Vector2<unsigned int>(3, 1))));
}


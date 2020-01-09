#include "UI_Window_HUD.h"

#include "World.h"
#include "Player.h"
#include "Player_Opposing.h"
#include "UI_Text.h"

UI_Window_HUD::UI_Window_HUD(const Vector2<float> argPosition)
	: UI_Window(argPosition)
{
	Init();
}

void UI_Window_HUD::Init()
{
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(20, 20), HAPI_TColour::RED, "Health", 35, "Data//font_pixel.ttf")));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(20, 60), HAPI_TColour::RED, "Current Remaining Enemies", 25, "Data//font_pixel.ttf")));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(20, 100), HAPI_TColour::RED, "Bosses Defeated", 25, "Data//font_pixel.ttf")));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(20, 140), HAPI_TColour::RED, "Score", 25, "Data//font_pixel.ttf")));

	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(550, 100), HAPI_TColour::RED, "Placement Stage", 65, "Data//font_pixel.ttf")));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(550, 200), HAPI_TColour::RED, "Currently Placing: ", 45, "Data//font_pixel.ttf")));
	elements.push_back(std::static_pointer_cast<UI_Element>(std::make_shared<UI_Text>(Vector2<float>(550, 240), HAPI_TColour::RED, "Placed: ", 45, "Data//font_pixel.ttf")));

}


void UI_Window_HUD::UpdateWindow()
{
	std::shared_ptr<Player>& player{ std::static_pointer_cast<Player>(WORLD.GetPlayer()) };

	std::static_pointer_cast<UI_Text>(elements[0])->SetText("Health: " + std::to_string(player->health));
	std::static_pointer_cast<UI_Text>(elements[1])->SetText("Current Remaining Enemies: " + std::to_string(WORLD.defatedEnemies) + " / " + std::to_string(WORLD.placedEnemies));
	std::static_pointer_cast<UI_Text>(elements[2])->SetText("Bosses Defeated: " + std::to_string(WORLD.bossesDefeated) + " / " + std::to_string(WORLD.requiredDefeatedBosses));
	std::static_pointer_cast<UI_Text>(elements[3])->SetText("Score: " + std::to_string(WORLD.score));

	std::shared_ptr<Player_Opposing>& opposingPlayer{ std::static_pointer_cast<Player_Opposing>(WORLD.GetOpposingPlayer()) };

	std::string currentlyPlacing{ "None" };
	switch (opposingPlayer->GetCurrentPlacement())
	{
	case ESpawnableEntities::eSlime:
		currentlyPlacing = "Normal Slime";
		break;

	case ESpawnableEntities::eSlime_Explosive:
		currentlyPlacing = "Explosive Slime";
		break;

	case ESpawnableEntities::eArcher:
		currentlyPlacing = "Archer";
		break;

	case ESpawnableEntities::eBat:
		currentlyPlacing = "Bat";
		break;

	case ESpawnableEntities::eSorcerer:
		currentlyPlacing = "Sorcerer";
		break;

	default:
		std::cerr << "ERROR: Changing HUD placement name but case isn't specified, placingEnumID=" << static_cast<int>(opposingPlayer->GetCurrentPlacement()) << std::endl;
		break;
	}

	std::static_pointer_cast<UI_Text>(elements[5])->SetText("Currently Placing: " + currentlyPlacing);
	std::static_pointer_cast<UI_Text>(elements[6])->SetText("Placed: " + std::to_string(WORLD.placedEnemies) + " / " + std::to_string(WORLD.maxPlaceEnemies));

	if (WORLD.sceneState == ESceneState::ePossession)
	{
		elements[0]->SetActive(true);
		elements[1]->SetActive(true);
		elements[2]->SetActive(true);
		elements[3]->SetActive(true);
		elements[4]->SetActive(false);
		elements[5]->SetActive(false);
		elements[6]->SetActive(false);
	}
	else if(WORLD.sceneState == ESceneState::ePlacement)
	{
		elements[0]->SetActive(false);
		elements[1]->SetActive(false);
		elements[2]->SetActive(false);
		elements[3]->SetActive(false);
		elements[4]->SetActive(true);
		elements[5]->SetActive(true);
		elements[6]->SetActive(true);
	}
	else
	{
		elements[0]->SetActive(false);
		elements[1]->SetActive(false);
		elements[2]->SetActive(false);
		elements[3]->SetActive(false);
		elements[4]->SetActive(false);
		elements[5]->SetActive(false);
		elements[6]->SetActive(false);
	}

	for (std::shared_ptr<UI_Element> element : elements)
	{
		if (element->GetActive())
			element->UpdateElement(*this);
	}
}
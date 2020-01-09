#include "UI_Button_Reward.h"

#include "World.h"
#include "Renderer.h"
#include "Player.h"

void UI_Button_Reward::OnBeginHover(UI_Window& argWindow)
{
}

void UI_Button_Reward::OnEndHover(UI_Window& argWindow)
{
}

void UI_Button_Reward::OnBeginClick(UI_Window& argWindow)
{
}

void UI_Button_Reward::OnEndClick(UI_Window& argWindow)
{
	std::shared_ptr<Player>& player{ std::static_pointer_cast<Player>(WORLD.GetPlayer()) };

	switch (rewardType)
	{
	case ERewardType::eHealth:
		player->maxHealth++;
		player->health = player->maxHealth;
		break;

	case ERewardType::eDamage:
		player->projectileDamage++;
		break;

	case ERewardType::eAttackSpeed:
		if (player->attackChargeTime > 0.5f)
			player->attackChargeTime -= 0.1f;
		break;

	default:
		std::cerr << "ERROR: Trying to apply reward but case isn't specified, RewardEnumID=" << static_cast<int>(rewardType) << std::endl;
		break;
	}

	WORLD.NextScene();
}

UI_Button_Reward::UI_Button_Reward(const Vector2<float> argButtonPosition, const Vector2<float> argButtonCollision, const Vector2<float> argTextPosition, const HAPI_TColour argTextColour, const std::string& argText, const int argTextSize, const std::string& argFontPath, const std::string& argButtonSprite, const std::string& argHoverSoundPath, const HAPI_TSoundOptions& argHoverSoundOptions, const std::string& argPressedSoundPath, const HAPI_TSoundOptions& argPressedSoundOptions, const Vector2<float> argImagePosition, const std::string& argImageSpritePath, const bool argImageHasAlpha, const Vector2<unsigned int> argImageTotalCells, const Vector2<unsigned int> argImageCurrentCells)
	: UI_Button(argButtonPosition, argButtonCollision, argTextPosition, argTextColour, argText, argTextSize, argFontPath, argButtonSprite, argHoverSoundPath, argHoverSoundOptions, argPressedSoundPath, argPressedSoundOptions), rewardImage(argImagePosition + argButtonPosition, argImageSpritePath, argImageHasAlpha, argImageTotalCells, argImageCurrentCells)

{
}

void UI_Button_Reward::DrawElement(const UI_Window& argWindow)
{
	Vector2<unsigned int> currentCells(1, static_cast<unsigned int>(buttonState));

	RENDERER.DrawSprite(buttonSprite, position + argWindow.position, currentCells);
	buttonLabel.DrawElement(argWindow);

	rewardImage.DrawElement(argWindow);
}

void UI_Button_Reward::ChangeReward()
{
	rewardType = static_cast<ERewardType>(rand() % static_cast<int>(ERewardType::eCount));
	rewardImage.SetCurrentCells(Vector2<unsigned int>(static_cast<unsigned int>(rewardType), 0));

	std::string buttonText;
	switch (rewardType)
	{
	case ERewardType::eHealth:
		buttonText = "Health Upgrade";
		break;

	case ERewardType::eDamage:
		buttonText = "Damage Upgrade";
		break;

	case ERewardType::eAttackSpeed:
		buttonText = "Attack Speed\n Upgrade";
		break;

	default:
		buttonText = "Unknown Upgrade";
		break;
	}

	buttonLabel.SetText(buttonText);
}

#pragma once
#include "UI_Button.h"

#include "UI_Element_Image.h"

// Type of reward which can be chosen
enum class ERewardType
{
	eDamage,
	eHealth,
	eAttackSpeed,
	eCount
};

class UI_Button_Reward : public UI_Button
{
private:
	ERewardType rewardType{ ERewardType::eHealth };
	UI_Element_Image rewardImage;

protected:
	// When mouse begins hovering
	virtual void OnBeginHover(UI_Window& argWindow) override final;
	// When mouse ends hovering
	virtual void OnEndHover(UI_Window& argWindow) override final;
	// When mouse starts clicking
	virtual void OnBeginClick(UI_Window& argWindow) override final;
	// When mouse ends clicking
	virtual void OnEndClick(UI_Window& argWindow) override final;

public:
	UI_Button_Reward(const Vector2<float> argButtonPosition = Vector2<float>(0, 0), const Vector2<float> argButtonCollision = Vector2<float>(20, 20), const Vector2<float> argTextPosition = Vector2<float>(0, 0), const HAPI_TColour argTextColour = HAPI_TColour::RED, const std::string& argText = "No Inputed Label Text", const int argTextSize = 10, const std::string & argFontPath = std::string(), const std::string & argButtonSprite = std::string(), const std::string& argHoverSoundPath = std::string(), const HAPI_TSoundOptions& argHoverSoundOptions = HAPI_TSoundOptions(), const std::string& argPressedSoundPath = std::string(), const HAPI_TSoundOptions& argPressedSoundOptions = HAPI_TSoundOptions(), const Vector2<float> argImagePosition = Vector2<float>(0, 0), const std::string& argImageSpritePath = std::string(), const bool argImageHasAlpha = false, const Vector2<unsigned int> argImageTotalCells = Vector2<unsigned int>(1, 1), const Vector2<unsigned int> argImageCurrentCells = Vector2<unsigned int>(0, 0));

	// Draws button image, text and the reward image
	virtual void DrawElement(const UI_Window& argWindow) override final;

	// Changes reward for button, allows for different rewards every enable
	void ChangeReward();
};


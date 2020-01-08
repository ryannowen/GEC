#pragma once
#include "UI_Element.h"

/// My Headers
#include "UI_Text.h"
#include "Rectangle.h"
#include "Vector2.h"
#include "UI_Window.h"

class UI_Button : public UI_Element
{
protected:
	enum class EButtonState
	{
		eNormal,
		eHover,
		ePressed
	};

	std::string hoverSoundPath;
	std::string pressedSoundPath;

	std::string buttonSprite;

	EButtonState buttonState{ EButtonState::eNormal };
	Rectangle buttonCollision;
	UI_Text buttonLabel;

	void MouseHoverCheck();


	// Overridable Game Mechanics (Pure)
	virtual void OnBeginHover(UI_Window& argWindow) = 0;
	virtual void OnEndHover(UI_Window& argWindow) = 0;
	virtual void OnBeginClick(UI_Window& argWindow) = 0;
	virtual void OnEndClick(UI_Window& argWindow) = 0;

public:
	UI_Button(const Vector2<float> argButtonPosition = Vector2<float>(0, 0), const Vector2<float> argButtonCollision = Vector2<float>(20, 20), const Vector2<float> argTextPosition = Vector2<float>(0, 0), const HAPI_TColour argTextColour = HAPI_TColour::RED, const std::string& argText = "No Inputed Label Text", const int argTextSize = 10, const std::string& argFontPath = std::string(), const std::string& argButtonSprite = std::string(), const std::string& argHoverSoundPath = std::string(), const HAPI_TSoundOptions& argHoverSoundOptions = HAPI_TSoundOptions(), const std::string& argPressedSoundPath = std::string(), const HAPI_TSoundOptions& argPressedSoundOptions = HAPI_TSoundOptions());

	//void LoadSoundBuffers(const Game* argGame, const std::string argHoverSound, const std::string argPressedSound);
	//void Draw(Game* argGame, sf::RenderWindow& window);

	virtual void UpdateElement(UI_Window& argWindow) override;
	virtual void DrawElement(const UI_Window& argWindow) override;

};

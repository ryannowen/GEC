#include "UI_Button.h"

#include "Renderer.h"
#include "Audio.h"
#include "UI_Window.h"

void UI_Button::MouseHoverCheck()
{
	
}

UI_Button::UI_Button(const Vector2<float> argButtonPosition, const Vector2<float> argButtonCollision, const Vector2<float> argTextPosition, const HAPI_TColour argTextColour, const std::string& argText, const int argTextSize, const std::string& argFontPath, const std::string& argButtonSprite, const std::string& argHoverSoundPath, const HAPI_TSoundOptions& argHoverSoundOptions, const std::string& argPressedSoundPath, const HAPI_TSoundOptions& argPressedSoundOptions)
	: UI_Element(argButtonPosition), buttonCollision(Rectangle(argButtonCollision.x, 0, argButtonCollision.y, 0)), buttonLabel(argTextPosition + argButtonPosition, argTextColour, argText, argTextSize, argFontPath), buttonSprite(argButtonSprite), hoverSoundPath(argHoverSoundPath), pressedSoundPath(argPressedSoundPath)
{
	AUDIO.LoadSound(argPressedSoundPath, argPressedSoundOptions);
	AUDIO.LoadSound(argHoverSoundPath, argHoverSoundOptions);
	RENDERER.CreateSprite(buttonSprite, false, Vector2<unsigned int>(1, 3));
}

void UI_Button::UpdateElement(UI_Window& argWindow)
{
	const HAPI_TMouseData& mouseData{ HAPI.GetMouseData() };
		
	buttonCollision.Translate(static_cast<int>(position.x), static_cast<int>(position.y));

	Rectangle mouseCollision{ Rectangle(mouseData.x, mouseData.x + 1, mouseData.y, mouseData.y + 1) };

	if (buttonCollision.Contains(mouseCollision))
	{
		if (buttonState == EButtonState::eHover && mouseData.leftButtonDown)
		{
			buttonState = EButtonState::ePressed;
			AUDIO.PlaySound(pressedSoundPath);
			OnBeginClick(argWindow);
		}
		else if (buttonState == EButtonState::eNormal)
		{
			buttonState = EButtonState::eHover;
			AUDIO.PlaySound(hoverSoundPath);
			OnBeginHover(argWindow);
		}
		else if (buttonState == EButtonState::ePressed && !mouseData.leftButtonDown)
		{
			buttonState = EButtonState::eNormal;
			OnEndClick(argWindow);
		}
	}
	else
	{
		if (buttonState == EButtonState::eHover)
		{
			buttonState = EButtonState::eNormal;
			OnEndHover(argWindow);
		}

		else if (buttonState == EButtonState::ePressed)
		{
			buttonState = EButtonState::eNormal;
			OnEndClick(argWindow);
		}
	}

	buttonCollision.Translate(static_cast<int>(-position.x), static_cast<int>(-position.y));
	
}
void UI_Button::DrawElement(const UI_Window& argWindow)
{
	Vector2<unsigned int> currentCells(1, static_cast<unsigned int>(buttonState));

	RENDERER.DrawSprite(buttonSprite, position + argWindow.position, currentCells);
	buttonLabel.DrawElement(argWindow);
}
#include "Controller.h"


Controller::Controller(std::vector<int> argKeyboardMovementKeys, std::vector<int> argControllerMovementKeys)
	: keyboardMovementKeys(argKeyboardMovementKeys), controllerMovementKeys(argControllerMovementKeys)
{
}

void Controller::SetKeyboardMovementKeys(std::vector<int> argKeyboardMovementKeys)
{
	keyboardMovementKeys = argKeyboardMovementKeys;
}

void Controller::SetControllerMovementKeys(std::vector<int> argControllerMovementKeys)
{
	controllerMovementKeys = argControllerMovementKeys;
}

Vector2<float> Controller::GetMovementDirection() const
{
	Vector2<float> direction(0, 0);

	HAPI_TControllerData controllerData{ HAPI.GetControllerData(0) };

	if (!controllerData.isAttached)
	{
		if (keyboardMovementKeys.size() <= 5 && keyboardMovementKeys.size() > 0)
		{
			HAPI_TKeyboardData keyboardData{ HAPI.GetKeyboardData() };

			direction = Vector2<float>((keyboardData.scanCode[keyboardMovementKeys[2]] ? 1.0f : keyboardData.scanCode[keyboardMovementKeys[3]] ? -1.0f : 0.0f),
				(keyboardData.scanCode[keyboardMovementKeys[0]] ? -1.0f : keyboardData.scanCode[keyboardMovementKeys[1]] ? 1.0f : 0.0f));

			direction.Normalise();
		}
	}
	else
	{
		if (controllerMovementKeys.size() <= 2 && controllerMovementKeys.size() > 0)
		{
			float xDir, yDir;
			if (controllerData.analogueButtons[controllerMovementKeys[0]] != 0)
				xDir = controllerData.analogueButtons[controllerMovementKeys[0]] / 32767.0f;
			
			if (controllerData.analogueButtons[controllerMovementKeys[1]] != 0)
				yDir = controllerData.analogueButtons[controllerMovementKeys[1]] / -32767.0f;

			direction = Vector2<float>((controllerData.analogueButtons[controllerMovementKeys[0]] > HK_GAMEPAD_LEFT_THUMB_DEADZONE ? xDir : controllerData.analogueButtons[controllerMovementKeys[0]] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE ? xDir : 0),
				(controllerData.analogueButtons[controllerMovementKeys[1]] > HK_GAMEPAD_LEFT_THUMB_DEADZONE ? yDir : controllerData.analogueButtons[controllerMovementKeys[1]] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE ? yDir : 0));
		}
	}

	return direction;
}

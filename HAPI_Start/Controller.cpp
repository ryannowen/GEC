#include "Controller.h"

#include "Entity.h"
#include "World.h"

Controller::Controller(const std::vector<int>& argKeyboardInput, const std::vector<int>& argControllerInput)
	: keyboardInput(argKeyboardInput), controllerInput(argControllerInput)
{
}

void Controller::Update(Entity& argEntity, const unsigned int argPlayerID)
{

}

void Controller::UpdateAnimDir(const EAction argRightAction, const EAction argLeftAction)
{
	if (GetFacingDirection())
		controllerAction = argRightAction;
	else
		controllerAction = argLeftAction;
}

bool Controller::GetFacingDirection() const
{
	if (controllerAction == EAction::eAttackRight || controllerAction == EAction::eMoveRight || controllerAction == EAction::eIdleRight)
		return true;
	else
		return false;
}

void Controller::SetKeyboardInput(const std::vector<int>& argKeyboardInput)
{
	keyboardInput = argKeyboardInput;
}

void Controller::SetControllerInput(const std::vector<int>& argControllerInput)
{
	controllerInput = argControllerInput;
}

Vector2<float> Controller::GetMovementDirection(const unsigned int argPlayerID) const
{
	Vector2<float> direction(0, 0);

	const HAPI_TControllerData& controllerData{ HAPI.GetControllerData(argPlayerID) };

	if (!controllerData.isAttached)
	{
		if (keyboardInput.size() >= 4)
		{
			const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

			float xDir{ keyboardData.scanCode[keyboardInput[2]] ? 1.0f : keyboardData.scanCode[keyboardInput[3]] ? -1.0f : 0.0f };
			float yDir{ keyboardData.scanCode[keyboardInput[0]] ? -1.0f : keyboardData.scanCode[keyboardInput[1]] ? 1.0f : 0.0f };

			direction = Vector2<float>(xDir, yDir);

			direction.Normalise();
		}
	}
	else
	{
		if (controllerInput.size() >= 2)
		{
			float xDir, yDir;
			if (controllerData.analogueButtons[controllerInput[1]] != 0)
				xDir = controllerData.analogueButtons[controllerInput[1]] / 32767.0f;

			if (controllerData.analogueButtons[controllerInput[0]] != 0)
				yDir = controllerData.analogueButtons[controllerInput[0]] / -32767.0f;

			direction.x = controllerData.analogueButtons[controllerInput[1]] > HK_GAMEPAD_LEFT_THUMB_DEADZONE ? xDir : controllerData.analogueButtons[controllerInput[1]] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE ? xDir : 0;
			direction.y = controllerData.analogueButtons[controllerInput[0]] > HK_GAMEPAD_LEFT_THUMB_DEADZONE ? yDir : controllerData.analogueButtons[controllerInput[0]] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE ? yDir : 0;
		}
	}

	return direction;
}

bool Controller::isJumping(const unsigned int argPlayerID)
{
	const HAPI_TControllerData& controllerData{ HAPI.GetControllerData(argPlayerID) };
	bool jumping{ false };
	if (!controllerData.isAttached)
	{
		const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

		jumping = keyboardData.scanCode[keyboardInput[4]];
	}
	else
	{
		jumping = controllerData.digitalButtons[controllerInput[2]];
	}

	if (jumping)
		controllerAction = EAction::eIdleRight;

	return jumping;
}

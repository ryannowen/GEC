#include "Controller_Bat.h"

#include "World.h"
#include "Bat.h"

void Controller_Bat::Update(Entity& argEntity, const unsigned int argPlayerID)
{
	Bat* bat = static_cast<Bat*>(&argEntity);
	if (bat->isPossessed) /// Player
	{
		const HAPI_TControllerData& controllerData{ HAPI.GetControllerData(argPlayerID) };

		if (controllerData.isAttached) /// Controller
		{
			Vector2<float> dir{ GetMovementDirection(argPlayerID) };

			if (controllerData.digitalButtons[controllerInput[3]])
			{
				if (bat->canAttack && !bat->isCharging)
				{
					bat->Attack();
					UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
				}
			}
			else if (static_cast<int>(dir.x) > 0 && !bat->isCharging)
				controllerAction = EAction::eIdleRight;
			else if (static_cast<int>(dir.x) < 0 && !bat->isCharging)
				controllerAction = EAction::eIdleLeft;
		}
		else
		{
			const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

			if (keyboardData.scanCode[keyboardInput[5]])
			{
				if (bat->canAttack && !bat->isCharging)
				{
					bat->Attack();
					UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
				}
			}
			else if (keyboardData.scanCode[keyboardInput[2]] && !bat->isCharging)
				controllerAction = EAction::eIdleRight;
			else if (keyboardData.scanCode[keyboardInput[3]] && !bat->isCharging)
				controllerAction = EAction::eIdleLeft;
		}
	}
	else /// AI
	{
		const std::shared_ptr<Entity>& player{ WORLD.GetPlayer() };

		const Vector2<float> dir{ player->GetPosition() - bat->currentPosition };

		const float dist{ dir.Dot() };

		if (dist > 32 && !bat->isCharging)
		{
			if (dir.x > 0)
				controllerAction = EAction::eIdleRight;
			else
				controllerAction = EAction::eIdleLeft;
		}
		else if (bat->canAttack && !bat->isCharging && dist <= 32)
		{
			bat->Attack();
			UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		}
		else if (bat->isCharging)
		{
			UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		}
	}
}

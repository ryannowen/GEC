#include "Controller_Slime_Boss.h"

#include "World.h"
#include "Slime_Boss.h"

void Controller_Slime_Boss::Update(Entity& argEntity, const unsigned int argPlayerID)
{
	Slime_Boss* slimeBoss = static_cast<Slime_Boss*>(&argEntity);
	if (slimeBoss->isPossessed) /// Player
	{
		const HAPI_TControllerData& controllerData{ HAPI.GetControllerData(argPlayerID) };

		if (controllerData.isAttached) /// Controller
		{
			Vector2<float> dir{ GetMovementDirection(argPlayerID) };

			if (controllerData.digitalButtons[controllerInput[3]])
			{
				if (!slimeBoss->isCharging)
				{
					slimeBoss->Attack();
					UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
				}
			}
			else if (static_cast<int>(dir.x) > 0 && !slimeBoss->isCharging)
				controllerAction = EAction::eMoveRight;
			else if (static_cast<int>(dir.x) < 0 && !slimeBoss->isCharging)
				controllerAction = EAction::eMoveLeft;
			else
				UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		}
		else /// Keyboard
		{
			const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

			if (keyboardData.scanCode[keyboardInput[5]])
			{
				if (!slimeBoss->isCharging)
				{
					slimeBoss->Attack();
					UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
				}
			}
			else if (keyboardData.scanCode[keyboardInput[2]] && !slimeBoss->isCharging)
				controllerAction = EAction::eMoveRight;
			else if (keyboardData.scanCode[keyboardInput[3]] && !slimeBoss->isCharging)
				controllerAction = EAction::eMoveLeft;
			else
				UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		}
	}
	else /// AI
	{
		const std::shared_ptr<Entity>& player{ WORLD.GetPlayer() };
		const Vector2<float> dir{ player->GetPosition() - slimeBoss->currentPosition };

		const float dist{ dir.Dot() };

		if (dist < 64 && !slimeBoss->isCharging)
		{
			if (dir.x < 0)
				controllerAction = EAction::eMoveRight;
			else
				controllerAction = EAction::eMoveLeft;
		}
		else if (dist >= 64 && !slimeBoss->isCharging)
		{
			if(slimeBoss->Attack())
				UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
		}
		else
		{
			UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		}
	}
}

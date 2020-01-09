#include "Controller_Slime.h"

#include "Slime.h"
#include "World.h"

void Controller_Slime::Update(Entity& argEntity, const unsigned int argPlayerID)
{
	Slime* slime = static_cast<Slime*>(&argEntity);
	if (slime->isPossessed) /// Player
	{
		const HAPI_TControllerData& controllerData{ HAPI.GetControllerData(argPlayerID) };

		if (slime->isAttacking)
			return;

		if (controllerData.isAttached) /// Controller
		{
			Vector2<float> dir{ GetMovementDirection(argPlayerID) };

			if (controllerData.digitalButtons[controllerInput[3]])
			{
				if (slime->canAttack && !slime->isCharging)
				{
					slime->Attack();
					UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
				}
			}
			else if (static_cast<int>(dir.x) > 0 && !slime->isCharging)
				controllerAction = EAction::eMoveRight;
			else if (static_cast<int>(dir.x) < 0 && !slime->isCharging)
				controllerAction = EAction::eMoveLeft;
			else
				UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		}
		else /// Keyboard
		{
			const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

			if (keyboardData.scanCode[keyboardInput[5]])
			{
				if (slime->canAttack && !slime->isCharging)
				{
					slime->Attack();
					UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
				}
			}
			else if (keyboardData.scanCode[keyboardInput[2]] && !slime->isCharging)
				controllerAction = EAction::eMoveRight;
			else if (keyboardData.scanCode[keyboardInput[3]] && !slime->isCharging)
				controllerAction = EAction::eMoveLeft;
			else
				UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		}
	}
	else /// AI
	{
		const std::shared_ptr<Entity>& player{ WORLD.GetPlayer() };
		const Vector2<float> dir{player->GetPosition() - slime->currentPosition };

		const float dist{ dir.Dot() };

		if (dist > 32 && !slime->isCharging && !slime->isAttacking)
		{
			if (dir.x > 0)
				controllerAction = EAction::eMoveRight;
			else
				controllerAction = EAction::eMoveLeft;
		}
		else if (slime->canAttack && !slime->isAttacking && dist < 32)
		{
			slime->Attack();
			UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
		}
		else if (!slime->isAttacking || slime->isCharging)
		{
			UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		}
	}
}

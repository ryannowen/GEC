#include "Controller_Sorcerer.h"

#include "World.h"
#include "Sorcerer.h"

void Controller_Sorcerer::Update(Entity& argEntity, const unsigned int argPlayerID)
{
	Sorcerer* sorcerer = static_cast<Sorcerer*>(&argEntity);

	if (sorcerer->isPossessed) /// Player
	{
		const HAPI_TControllerData& controllerData{ HAPI.GetControllerData(argPlayerID) };

		if (sorcerer->isAttacking)
			return;

		/// Keyboard 
		if (!controllerData.isAttached)
		{
			const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

			if (keyboardData.scanCode[keyboardInput[5]])
			{
				if (sorcerer->canAttack && !sorcerer->isCharging)
				{
					if (sorcerer->Attack(GetMovementDirection(1)))
						UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
				}
			}
			else if (keyboardData.scanCode[keyboardInput[2]] && !sorcerer->isCharging)
				controllerAction = EAction::eIdleRight;
			else if (keyboardData.scanCode[keyboardInput[3]] && !sorcerer->isCharging)
				controllerAction = EAction::eIdleLeft;
			else if (!sorcerer->isAttacking || sorcerer->isCharging)
			{
				UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
			}
		}
		else /// Controller
		{

		}
	}
	else /// AI
	{
		const std::shared_ptr<Entity> player{ WORLD.GetPlayer() };

		const Vector2<float> dir{ (player->currentPosition + Vector2<float>(sorcerer->collisionBounds.Width() / 2.0f, sorcerer->collisionBounds.Height() / 2.0f)) - sorcerer->currentPosition };

		if (sorcerer->canAttack && !sorcerer->isAttacking && !sorcerer->isCharging)
		{
			Vector2<float> tempDir{ dir };
			tempDir.Normalise();

			if (sorcerer->Attack(tempDir))
			{
				if (dir.x > 0)
					controllerAction = EAction::eIdleRight;
				else
					controllerAction = EAction::eIdleLeft;

				UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
			}
		}
		else if (!sorcerer->isAttacking || sorcerer->isCharging)
		{
			UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		}


	}

}

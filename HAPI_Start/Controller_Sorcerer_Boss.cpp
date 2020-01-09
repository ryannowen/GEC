#include "Controller_Sorcerer_Boss.h"

#include "World.h"
#include "Sorcerer_Boss.h"

void Controller_Sorcerer_Boss::Update(Entity& argEntity, const unsigned int argPlayerID)
{
	Sorcerer_Boss* sorcererBoss = static_cast<Sorcerer_Boss*>(&argEntity);

	if (sorcererBoss->isPossessed) /// Player
	{
		const HAPI_TControllerData& controllerData{ HAPI.GetControllerData(argPlayerID) };

		if (sorcererBoss->isAttacking)
			return;

		
		if (controllerData.isAttached) /// Controller
		{
			Vector2<float> dir{ GetMovementDirection(argPlayerID) };

			if (controllerData.digitalButtons[controllerInput[3]])
			{
				if (sorcererBoss->canAttack && !sorcererBoss->isCharging)
				{
					if (sorcererBoss->Attack(GetMovementDirection(argPlayerID)))
						UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
				}
			}
			else if (static_cast<int>(dir.x) > 0 && !sorcererBoss->isCharging)
				controllerAction = EAction::eIdleRight;
			else if (static_cast<int>(dir.x) < 0 && !sorcererBoss->isCharging)
				controllerAction = EAction::eIdleLeft;
			else if (!sorcererBoss->isAttacking || sorcererBoss->isCharging)
				UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
			
		}
		else  /// Keyboard 
		{
			const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

			if (keyboardData.scanCode[keyboardInput[5]])
			{
				if (sorcererBoss->canAttack && !sorcererBoss->isCharging)
				{
					if (sorcererBoss->Attack(GetMovementDirection(argPlayerID)))
						UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
				}
			}
			else if (keyboardData.scanCode[keyboardInput[2]] && !sorcererBoss->isCharging)
				controllerAction = EAction::eIdleRight;
			else if (keyboardData.scanCode[keyboardInput[3]] && !sorcererBoss->isCharging)
				controllerAction = EAction::eIdleLeft;
			else if (!sorcererBoss->isAttacking || sorcererBoss->isCharging)
				UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
			
		}
	}
	else /// AI
	{
		const std::shared_ptr<Entity>& player{ WORLD.GetPlayer() };

		const Vector2<float> dir{ (player->GetPosition() + Vector2<float>(sorcererBoss->collisionBounds.Width() / 2.0f, sorcererBoss->collisionBounds.Height() / 2.0f)) - sorcererBoss->currentPosition };

		if (sorcererBoss->canAttack && !sorcererBoss->isAttacking && !sorcererBoss->isCharging)
		{
			Vector2<float> tempDir{ dir };
			tempDir.Normalise();

			if (sorcererBoss->Attack(tempDir))
			{
				if (dir.x > 0)
					controllerAction = EAction::eIdleRight;
				else
					controllerAction = EAction::eIdleLeft;

				UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
			}
		}
		else if (!sorcererBoss->isAttacking || sorcererBoss->isCharging)
		{
			UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		}
	}
}

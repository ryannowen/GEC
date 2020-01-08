#include "Controller_Archer.h"

#include "World.h"
#include "Archer.h"

void Controller_Archer::Update(Entity& argEntity, const unsigned int argPlayerID)
{
	Archer* archer = static_cast<Archer*>(&argEntity);
	
	if (archer->isPossessed) /// Player
	{
		const HAPI_TControllerData& controllerData{ HAPI.GetControllerData(argPlayerID) };

		if (archer->isAttacking)
			return;

		/// Keyboard 
		if (!controllerData.isAttached)
		{
			const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

			if (keyboardData.scanCode[keyboardInput[5]])
			{
				if (archer->canAttack && !archer->isCharging)
				{
					if (archer->Attack(GetMovementDirection(1)))
						UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
				}
			}
			else if (keyboardData.scanCode[keyboardInput[2]] && !archer->isCharging)
				controllerAction = EAction::eIdleRight;
			else if (keyboardData.scanCode[keyboardInput[3]] && !archer->isCharging)
				controllerAction = EAction::eIdleLeft;
			else if (!archer->isAttacking || archer->isCharging)
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

		const Vector2<float> dir{ (player->currentPosition + Vector2<float>(archer->collisionBounds.Width() / 2.0f, archer->collisionBounds.Height() / 2.0f)) - archer->currentPosition };

		if (archer->canAttack && !archer->isAttacking && !archer->isCharging)
		{
			Vector2<float> tempDir{ dir };
			tempDir.Normalise();

			if (archer->Attack(tempDir))
			{
				if (dir.x > 0)
					controllerAction = EAction::eIdleRight;
				else
					controllerAction = EAction::eIdleLeft;

				UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
			}
		}
		else if (!archer->isAttacking || archer->isCharging)
		{
			UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		}

		
	}
}

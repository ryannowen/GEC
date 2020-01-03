#include "Controller_Player.h"

#include "Player.h"



void Controller_Player::Update(Entity& argEntity, const unsigned int argPlayerID)
{
	const HAPI_TControllerData& controllerData{ HAPI.GetControllerData(argPlayerID) };
	Player* player = static_cast<Player*>(&argEntity);

	if (!controllerData.isAttached)
	{
		const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

		if (keyboardData.scanCode[keyboardInput[5]])
		{
			if (player->CanAttack())
			{
				UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
				player->Attack();
			}
		}
		else if (keyboardData.scanCode[keyboardInput[2]])
			controllerAction = EAction::eMoveRight;
		else if (keyboardData.scanCode[keyboardInput[3]])
			controllerAction = EAction::eMoveLeft;
		else if (keyboardData.scanCode[keyboardInput[4]])
			UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
		else
			UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);



		
	}
	else
	{

	}
}

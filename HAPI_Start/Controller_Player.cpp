#include "Controller_Player.h"

#include "World.h"
#include "Player.h"

void Controller_Player::Update(Entity& argEntity, const unsigned int argPlayerID)
{
	const HAPI_TControllerData& controllerData{ HAPI.GetControllerData(argPlayerID) };
	Player* player = static_cast<Player*>(&argEntity);

	if (controllerData.isAttached) /// Controller
	{
		Vector2<float> dir{ GetMovementDirection(argPlayerID) };

		if (controllerData.digitalButtons[controllerInput[3]] && player->canAttack)
		{
			if (player->Attack())
				UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
		}
		else if (static_cast<int>(dir.x) > 0)
			controllerAction = EAction::eMoveRight;
		else if (static_cast<int>(dir.x) < 0)
			controllerAction = EAction::eMoveLeft;
		else if (!player->isAttacking)
			UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
	}
	else /// Keyboard
	{
		const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

		if (keyboardData.scanCode[keyboardInput[5]] && player->canAttack)
		{
			if (player->Attack())
				UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
		}
		else if (keyboardData.scanCode[keyboardInput[2]])
			controllerAction = EAction::eMoveRight;
		else if (keyboardData.scanCode[keyboardInput[3]])
			controllerAction = EAction::eMoveLeft;
		else if (!player->isAttacking)
			UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);

		
	}
}

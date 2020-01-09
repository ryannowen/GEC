#include "Controller_OpposingPlayer.h"

#include "Player_Opposing.h"
#include "World.h"
#include "Time.h"

void Controller_OpposingPlayer::Action(Player_Opposing* argPlayer)
{
	argPlayer->canAction = false;

	if (WORLD.GetSceneState() == ESceneState::ePlacement)
		argPlayer->PlaceEntity();
	else if (WORLD.GetSceneState() == ESceneState::ePossession)
		argPlayer->PossessEntity();
}

void Controller_OpposingPlayer::Update(Entity& argEntity, const unsigned int argPlayerID)
{
	const HAPI_TControllerData& controllerData{ HAPI.GetControllerData(argPlayerID) };
	Player_Opposing* playerOpposing = static_cast<Player_Opposing*>(&argEntity);

	if (controllerData.isAttached) /// Controller
	{
		if (controllerData.digitalButtons[controllerInput[2]])
		{
			playerOpposing->ChangePlacementEntity();
		}
		else if (controllerData.digitalButtons[controllerInput[3]] && playerOpposing->canAction)
		{
			Action(playerOpposing);
		}
	}
	else /// Keyboard
	{
		const HAPI_TKeyboardData& keyboardData{ HAPI.GetKeyboardData() };

		if (keyboardData.scanCode[keyboardInput[4]])
		{
			playerOpposing->ChangePlacementEntity();
		}
		else if (keyboardData.scanCode[keyboardInput[5]] && playerOpposing->canAction)
		{
			Action(playerOpposing);
		}
	}

}


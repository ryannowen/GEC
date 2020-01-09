#pragma once
#include "Controller.h"

#include "Player_Opposing.h"

class Controller_OpposingPlayer : public Controller
{
private:
	// Triggers Possession or Placement for opposing player
	void Action(Player_Opposing* argPlayer);

public:
	// Updates controller and owner entity data
	virtual void Update(Entity& argEntity, const unsigned int argPlayerID) override final;
};


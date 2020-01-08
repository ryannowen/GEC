#pragma once
#include "Controller.h"

#include "Player_Opposing.h"

class Controller_OpposingPlayer : public Controller
{
private:
	void Action(Player_Opposing* argPlayer);
	bool canAction{ true };
	const float actionDelayTime{ 1.0f };
	float actionDelay{ 0 };

public:
	virtual void Update(Entity& argEntity, const unsigned int argPlayerID) override final;

};


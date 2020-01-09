#pragma once
#include "Controller.h"
class Controller_Sorcerer : public Controller
{
public:
	// Updates controller and owner entity data
	virtual void Update(Entity& argEntity, const unsigned int argPlayerID) override final;
};


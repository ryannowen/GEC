#pragma once
#include "Controller.h"

#include "Archer.h"

class Controller_Archer : public Controller
{
public:
	// Updates controller and owner entity data
	virtual void Update(Entity& argEntity, const unsigned int argPlayerID) override final;
};


#pragma once
#include "Controller.h"

#include "Archer.h"

class Controller_Archer : public Controller
{
public:
	virtual void Update(Entity& argEntity, const unsigned int argPlayerID) override final;
};


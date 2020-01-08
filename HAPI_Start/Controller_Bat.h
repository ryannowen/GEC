#pragma once
#include "Controller.h"
class Controller_Bat : public Controller
{
public:
	virtual void Update(Entity& argEntity, const unsigned int argPlayerID) override final;

};


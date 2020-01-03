#pragma once
#include "Controller.h"
class Controller_Player : public Controller
{
private:

public:
	virtual void Update(Entity& argEntity, const unsigned int argPlayerID) override;

};


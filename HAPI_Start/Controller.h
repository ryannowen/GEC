#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

#include "Vector2.h"
#include <vector>

class Controller
{
private:
	std::vector<int> keyboardMovementKeys;
	std::vector<int> controllerMovementKeys;

public:
	Controller(std::vector<int> argMovementKeyboardKeys = std::vector<int>(), std::vector<int> argControllerMovementKeys = std::vector<int>());

	void SetKeyboardMovementKeys(std::vector<int> argKeyboardMovementKeys);
	void SetControllerMovementKeys(std::vector<int> argControllerMovementKeys);
	Vector2<float> GetMovementDirection() const;

};


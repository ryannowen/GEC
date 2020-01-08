#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

/// My headers
#include "Vector2.h"

class UI_Window;

class UI_Element
{
protected:
	bool active{ true };

	Vector2<float> position{ 0, 0 };

public:
	UI_Element(const Vector2<float> argPosition);
	virtual void UpdateElement(UI_Window& argWindow) = 0;
	virtual void DrawElement(const UI_Window& argWindow) = 0;

	void SetPosition(Vector2<float> argPosition) { position = argPosition; };
	void SetActive(const bool argActive) { active = argActive; };
	bool GetActive() const { return active; };
};


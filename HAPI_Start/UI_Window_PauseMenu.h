#pragma once
#include "UI_Window.h"
class UI_Window_PauseMenu : public UI_Window
{
public:
	UI_Window_PauseMenu(const Vector2<float> argPosition);

	virtual void Init() override final;
};


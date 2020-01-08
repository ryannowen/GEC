#pragma once
#include "UI_Window.h"
class UI_Window_HUD : public UI_Window
{
public:
	UI_Window_HUD(const Vector2<float> argPosition);

	virtual void Init() override final;
	virtual void UpdateWindow() override final;
};


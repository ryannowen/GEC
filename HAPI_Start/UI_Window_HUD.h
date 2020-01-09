#pragma once
#include "UI_Window.h"
class UI_Window_HUD : public UI_Window
{
public:
	UI_Window_HUD(const Vector2<float> argPosition);

	// Init function for creating window elements
	virtual void Init() override final;

	// Updates all window elements
	virtual void UpdateWindow() override final;
};


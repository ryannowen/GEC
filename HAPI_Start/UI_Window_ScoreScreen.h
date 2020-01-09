#pragma once
#include "UI_Window.h"
class UI_Window_ScoreScreen : public UI_Window
{
protected:
	// When window is enabled
	virtual void OnEnable();

public:
	UI_Window_ScoreScreen(const Vector2<float> argPosition);

	// Init function for creating window elements
	virtual void Init() override final;
};


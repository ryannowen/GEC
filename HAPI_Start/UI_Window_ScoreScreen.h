#pragma once
#include "UI_Window.h"
class UI_Window_ScoreScreen : public UI_Window
{
protected:
	virtual void OnEnabled();

public:
	UI_Window_ScoreScreen(const Vector2<float> argPosition);

	virtual void Init() override final;
	virtual void UpdateWindow() override final;
};


#pragma once
#include "UI_Window.h"
class UI_Window_Reward : public UI_Window
{
protected:
	// When window is enabled
	virtual void OnEnable() override final;

public:
	UI_Window_Reward(const Vector2<float> argPosition);

	// Init function for creating window elements
	virtual void Init() override final;
};


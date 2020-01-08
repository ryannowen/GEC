#pragma once
#include "UI_Window.h"
class UI_Window_Reward : public UI_Window
{
protected:
	virtual void OnEnabled() override final;

public:
	UI_Window_Reward(const Vector2<float> argPosition);

	virtual void Init() override final;
};


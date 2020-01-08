#pragma once

#include <vector>
#include <memory>

/// My headers
#include "UI_Element.h"

class UI_Window
{
private:
	friend class UI_Interface;
	friend class UI_Text;
	friend class UI_Element_Image;
	friend class UI_Button;
	friend class UI_Button_Reward;

	bool active{ false };
protected:
	std::vector<std::shared_ptr<UI_Element>> elements;
	Vector2<float> position{ 0, 0 };

	virtual void OnEnabled();
	virtual void OnDisabled();

public:
	UI_Window(const Vector2<float> argPosition);

	virtual void Init() = 0;
	virtual void UpdateWindow();
	void DrawWindow() const;

	void SetActive(const bool argActive);
};


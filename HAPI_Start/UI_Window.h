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

	// When window is enabled
	virtual void OnEnable();

	// When window is disabled
	virtual void OnDisable();

public:
	UI_Window(const Vector2<float> argPosition);

	// Init function for creating window elements
	virtual void Init() = 0;

	// Updates all window elements
	virtual void UpdateWindow();

	// Draws all window elements to screen
	void DrawWindow() const;

	// Changes active state of window, and actives OnEnable/Disable
	void SetActive(const bool argActive);
};


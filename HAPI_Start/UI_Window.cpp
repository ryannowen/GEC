#include "UI_Window.h"


void UI_Window::OnEnabled()
{
}

void UI_Window::OnDisabled()
{
}

UI_Window::UI_Window(const Vector2<float> argPosition)
	: position(argPosition)
{
}

void UI_Window::UpdateWindow()
{
	for (std::shared_ptr<UI_Element> element : elements)
	{
		if (element->GetActive())
			element->UpdateElement(*this);
	}
}

void UI_Window::DrawWindow() const
{
	for (std::shared_ptr<UI_Element> element : elements)
	{
		if(element->GetActive())
			element->DrawElement(*this);
	}
}

void UI_Window::SetActive(const bool argActive)
{
	active = argActive;

	if (active)
		OnEnabled();
	else
		OnDisabled();
}

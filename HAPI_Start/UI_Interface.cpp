#include "UI_Interface.h"

std::shared_ptr<UI_Interface> UI_Interface::userInterface{ nullptr };


UI_Interface::UI_Interface()
{
}

void UI_Interface::UpdateWindows()
{
	for (auto window : windowMap)
	{
		if (window.second->active)
			window.second->UpdateWindow();
	}
}

void UI_Interface::DrawWindows()
{
	for (auto window : windowMap)
	{
		if (window.second->active)
			window.second->DrawWindow();
	}
}

bool UI_Interface::CreateWindow(const std::string& argName, const std::shared_ptr<UI_Window> argWindow)
{
	if (windowMap.find(argName) != windowMap.end())
	{
		std::cerr << "ERROR: Window with name already created, name=" << argName << std::endl;
		return false;
	}
	else
	{
		windowMap[argName] = argWindow;
		return true;
	}
	
}

void UI_Interface::SetWindowActive(const std::string& argName, const bool argActive)
{
	if (windowMap.find(argName) == windowMap.end())
	{
		std::cerr << "ERROR: Couldn't find specified window, name=" << argName << std::endl;
		return;
	}
	else
	{
		windowMap.find(argName)->second->SetActive(argActive);
	}

}

void UI_Interface::HideAllWindows()
{
	for (auto window : windowMap)
	{
		if (window.second->active)
			window.second->SetActive(false);
	}
}

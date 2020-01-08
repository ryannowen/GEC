#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

#include <unordered_map>

#include "UI_Window.h"

class UI_Interface
{
private:
	UI_Interface();
	
	static std::shared_ptr<UI_Interface> userInterface;
	std::unordered_map<std::string, std::shared_ptr<UI_Window>> windowMap;
public:
	static UI_Interface& GetInstance()
	{
		if (!userInterface)
		{
			userInterface.reset(new UI_Interface());
		}

		return *userInterface;
	}

	void UpdateWindows();
	void DrawWindows();
	bool CreateWindow(const std::string& argName, const std::shared_ptr<UI_Window> argWindow);
	void SetWindowActive(const std::string& argName, const bool argActive);
	void HideAllWindows();
};

#define UI UI_Interface::GetInstance()

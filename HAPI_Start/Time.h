#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

// C++ Headers
#include <list>

class Time
{
private:
	float deltaTime{ 0 };
	float tick{ 0 };
	bool hasTicked{ false };

	DWORD tickLength{ 50 };
	DWORD currentTime{ HAPI.GetTime() };
	DWORD elapsedTime{ HAPI.GetTime() };

	Time() = default;

	static Time* time;

public:
	void Update();

	/// Returns Delta time in Milliseconds
	float GetDeltaTimeMiliseconds() { return deltaTime; };
	float GetDeltaTimeSeconds() { return deltaTime / 1000.0f; };

	bool GetHasTicked(){ return hasTicked; };
	DWORD GetTickLength() { return tickLength; };

	float GetTickTimeMiliseconds() { return tick; };
	float GetTickTimeSeconds() { return tick / 1000.0f; };

	DWORD GetCurrentTime() { return currentTime; };
	DWORD GetElapsedTime() { return elapsedTime; };

	float CalculateInterp() { return static_cast<float>(currentTime - elapsedTime) / tickLength; };

	void DeleteInstance();

	static Time& GetTime();
};

#define TIME Time::GetTime()

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

	static std::shared_ptr<Time> time;

public:
	static Time& GetInstance()
	{
		if (time == nullptr)
		{
			time.reset(new Time());
		}

		return *time;
	}

	// Updates time
	void Update();

	// Returns Delta time in Milliseconds
	float GetDeltaTimeMiliseconds() { return deltaTime; };
	// Returns Delta time in Seconds
	float GetDeltaTimeSeconds() { return deltaTime / 1000.0f; };

	// Returns true if time has ticked
	bool GetHasTicked(){ return hasTicked; };
	// Returns the length of a tick (In Milliseconds)
	DWORD GetTickLength() { return tickLength; };

	// Returns Tick time in Milliseconds
	float GetTickTimeMiliseconds() { return tick; };
	// Returns Tick time in Seconds
	float GetTickTimeSeconds() { return tick / 1000.0f; };

	// Returns current time
	DWORD GetCurrentTime() { return currentTime; };

	// Returns elapsed time
	DWORD GetElapsedTime() { return elapsedTime; };

	// Returns calculated interpolation for frame
	float CalculateInterp() { return static_cast<float>(currentTime - elapsedTime) / tickLength; };

	
};

#define TIME Time::GetInstance()

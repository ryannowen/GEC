#include "Time.h"

Time* Time::time{ nullptr };

/// Calculates Deleta time, Updates Elapsed time and progresses timers
void Time::Update()
{
	hasTicked = false;
	deltaTime = static_cast<float>(HAPI.GetTime() - currentTime);
	currentTime = HAPI.GetTime();

	if (currentTime - elapsedTime > tickLength)
	{
		tick = currentTime - elapsedTime;
		elapsedTime = HAPI.GetTime();
		hasTicked = true;
	}
}

void Time::DeleteInstance()
{
	delete time;
}

Time& Time::GetTime()
{
	if (time == nullptr)
	{
		time = new Time();
	}

	return *time;
}



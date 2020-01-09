#include "Time.h"

std::shared_ptr<Time> Time::time{ nullptr };

/// Calculates Deleta time, Updates Elapsed time and progresses timers
void Time::Update()
{
	hasTicked = false;
	deltaTime = static_cast<float>(HAPI.GetTime() - currentTime);
	currentTime = HAPI.GetTime();

	float time{ static_cast<float>(currentTime - elapsedTime) };

	if (time > tickLength * 2) /// Prevents Freeze and skip
	{
		tick = 0;
		elapsedTime = HAPI.GetTime();
	}
	else if (time > tickLength)
	{
		tick = time;
		elapsedTime = HAPI.GetTime();
		hasTicked = true;
	}
}


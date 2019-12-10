#include "Time.h"

std::shared_ptr<Time> Time::time{ nullptr };

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


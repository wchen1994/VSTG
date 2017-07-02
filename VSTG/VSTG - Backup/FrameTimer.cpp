#include "FrameTimer.h"

FrameTimer::FrameTimer()
{
	lasttime = curtime = std::chrono::steady_clock::now();
}

float FrameTimer::Mark()
{
	curtime = std::chrono::steady_clock::now();
	std::chrono::duration<float> runtime = curtime - lasttime;
	lasttime = curtime;
	// return in microsecond
	return runtime.count();
}

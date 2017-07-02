#pragma once

#include <chrono>

class FrameTimer {
public:
	FrameTimer();
	float Mark();
private:
	std::chrono::steady_clock::time_point curtime;
	std::chrono::steady_clock::time_point lasttime;
};
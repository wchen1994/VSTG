#pragma once

#include "Defines.h"
#include <chrono>

namespace CommResMeth {
	class __VSTG_API FrameTimer {
	public:
		FrameTimer();
		float Mark();
	private:
		std::chrono::steady_clock::time_point curtime;
		std::chrono::steady_clock::time_point lasttime;
	};
}
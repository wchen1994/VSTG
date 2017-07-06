#include "SceneBulletHell.h"
#include "FrameTimer.h"

#define __TEST_1

#ifdef __TEST_1

#pragma comment(lib, "CommonResourcesMethods")
#pragma comment(lib, "SceneBulletHell")

int main() {
	DllSceneBulletHell::SceneBulletHell sceneMain(nullptr);

	return sceneMain.exec();
}

#endif
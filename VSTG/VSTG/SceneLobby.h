#pragma once

#include "Scene.hpp"
#include "Button.h"

class SceneLobby : Scene {
public:
	SceneLobby();
	Essential::GameState Run();
private:
	Button butHost;
	Button butJoin;
};

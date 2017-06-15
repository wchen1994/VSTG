#pragma once

#include "Scene.hpp"
#include "Button.h"
#include "ObjMenu.h"

class SceneLobby : public Scene {
public:
	SceneLobby();
	Essential::GameState Run();
private:
	Button butHost;
	Button butJoin;
	Button butBack;
	ObjMenu hostMenu;
	bool isHostMenu;
};

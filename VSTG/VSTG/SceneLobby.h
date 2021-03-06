#pragma once

#include "Scene.hpp"
#include "Button.h"
#include "ObjMenu.h"
#include "TextBox.h"

class SceneLobby : public Scene {
public:
	SceneLobby();
	Essential::GameState Run();
private:
	Button butHost;
	Button butJoin;
	Button butBack;
	ObjMenu hostMenu;
	ObjMenu clientMenu;
	bool isHostMenu;
	bool isClientMenu;
	TextBox boxHostPort;
	TextBox boxClientIP;
	TextBox boxClientPort;
	TextBox boxLocalPort;

	int playerCounter;
	bool isClientConnecting;
	bool isClientConnected;
};

#pragma once

#include "Scene.hpp"
#include "Essential.hpp"
#include "Button.h"

class SceneStartMenu : public Scene{
private:
	sf::Event event;
	sf::RenderWindow& wnd;
	std::shared_ptr<sf::Texture> butTexture;
	Button butStart;
	Button butOnline;
	Button butEdit;
	Button butExit;
	bool isFocus;
public:
	SceneStartMenu(sf::RenderWindow& wnd);
	virtual ~SceneStartMenu() = default;
	Essential::GameState Run();
};

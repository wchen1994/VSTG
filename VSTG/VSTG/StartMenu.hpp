#pragma once

#include "Scene.hpp"
#include "Essential.hpp"
#include "Button.h"

class StartMenu : public Scene{
private:
	sf::Event event;
	sf::RenderWindow& wnd;
	std::shared_ptr<sf::Texture> butTexture;
	Button butStart;
	Button butEdit;
	Button butExit;
public:
	StartMenu(sf::RenderWindow& wnd);
	virtual ~StartMenu() = default;
	Essential::GameState Run();
};

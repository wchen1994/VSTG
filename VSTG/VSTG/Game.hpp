#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

#include "GameObject.hpp"
#include "Scene.hpp"
#include "Essential.hpp"

class Game : public Scene{
private:
	sf::Event event;
	sf::RenderWindow& wnd;
public:
	Game(sf::RenderWindow& wnd);
	~Game();
	Essential::GameState Run();
	void Update();
public:
	static std::set<GameObject*> layerDefault;
	static std::set<GameObject*> layerDelete;
};

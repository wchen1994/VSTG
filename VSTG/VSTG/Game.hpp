#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

#include "GameObject.hpp"
#include "Scene.hpp"
#include "Essential.hpp"
#include "FrameTimer.h"
#include "Board.hpp"
#include "Map.h"

class Game : public Scene{
private:
	sf::Event event;
	sf::RenderWindow& wnd;
	FrameTimer ft;
	float dt;//Delta time
	float culDt = 0.0f;//Culmulative delta time
	float logTimer = 0.0f;
	static constexpr float fixedUpdateDuration = 1 / 60.0f;
	size_t nDeletes = 0;
	Map map;
public:
	Game(sf::RenderWindow& wnd);
	~Game();
	Essential::GameState Run();
	void Update();
public:
	static std::set<std::shared_ptr<GameObject>> layerDefault;
	static std::set<std::shared_ptr<GameObject>> layerBullet;
	static std::set<std::shared_ptr<GameObject>> layerPlayer;
	static std::set<std::shared_ptr<GameObject>> layerDelete;
	static Board brd;
	static constexpr int tileWidth = 50;
	static constexpr int tileHeight = 50;

#ifdef _BOARD_DEBUG
private:
	std::vector<sf::Vector2i> vHLPos;
#endif
};

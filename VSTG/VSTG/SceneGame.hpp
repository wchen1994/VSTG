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
#include "ObjMenu.h"
#include "ObjCreator.h"

//#define _DEBUG_BOARD
#define _DEBUG_LOG

class SceneGame : public Scene{
private:
	sf::Event event;
	sf::RenderWindow& wnd;
	FrameTimer ft;
	float dt;//Delta time
	float culDt = 0.0f;//Culmulative delta time
	float logTimer = 0.0f;
	static constexpr float fixedUpdateDuration = 1 / 60.0f;
	size_t nDeletes = 0;
	bool isFocused;
	bool isMenuTriger;
	bool isGamePause;
	Map map;
	ObjMenu escMenu;
	sf::RectangleShape background;
public:
	SceneGame(sf::RenderWindow& wnd);
	~SceneGame();
	Essential::GameState Run();
	void Update();
	void DrawScene();
public:
	static std::set<std::shared_ptr<ObjCharacter>> layerDefault;
	static std::set<std::shared_ptr<ObjCharacter>> layerBullet;
	static std::set<std::shared_ptr<ObjCharacter>> layerPlayer;
	static std::set<std::shared_ptr<ObjCharacter>> layerEnemy;	
	static std::set<std::shared_ptr<ObjCharacter>> layerDelete;
	static Board brd;

	// Changing the tile size require to rebuild the soluction
	static constexpr int tileWidth = 20;
	static constexpr int tileHeight = 20;
};

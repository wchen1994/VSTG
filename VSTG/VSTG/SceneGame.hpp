#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
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
//#define _DEBUG_LOG

class SceneGame : public Scene{
private:
	sf::Event event;
	sf::RenderWindow& wnd;
	FrameTimer ft;
	float dt;//Delta time
	float culDt = 0.0f;//Culmulative delta time
	float logTimer = 0.0f;
	static constexpr float fixedUpdateDuration = 1 / 30.0f;
	unsigned int nDeletes = 0;
	bool isFocused;
	bool isMenuTriger;
	bool isGamePause;
	bool isGameFail;
	bool isGameSucceed;
	Map map;
	int levelCount;
	std::string levelFileName;
	ObjMenu escMenu;
	sf::RectangleShape background; 
	std::shared_ptr<ObjPlayer> pPlayer;

	// UI
	sf::Text playerHP;
public:
	SceneGame(sf::RenderWindow& wnd);
	~SceneGame();
	Essential::GameState Run();
	void Reset();
	void Update();
	void DrawScene();
public:
	static std::set<std::shared_ptr<ObjCharacter>> layerDefault;
	static std::set<std::shared_ptr<ObjCharacter>> layerBullet;
	static std::vector<std::shared_ptr<ObjCharacter>> layerPlayer;
	static std::set<std::shared_ptr<ObjCharacter>> layerEnemy;	
	static std::set<std::shared_ptr<ObjCharacter>> layerEnemyBullet;
	static std::set<std::shared_ptr<ObjCharacter>> layerDelete;
	static Board brd;

	// Changing the tile size require to rebuild the soluction
	static constexpr int tileWidth = 20;
	static constexpr int tileHeight = 20;
};

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
#include "Menu.h"
#include "ObjCreator.h"
#include <Scene.hpp>

#pragma comment(lib, "CommonResourcesMethods")

#define _DEBUG_BOARD
#define _DEBUG_LOG

class SceneBulletHell : public CommResMeth::Scene{
private:
	sf::Event event;
	CommResMeth::FrameTimer ft;
	float dt;//Delta time
	float culDt = 0.0f;//Culmulative delta time
	float logTimer = 0.0f;
	static constexpr float fixedUpdateDuration = 1 / 30.0f;
	size_t nDeletes = 0;
	bool isFocused;
	bool isMenuTriger;
	bool isGamePause;
	bool isGameFail;
	bool isGameSucceed;
	Map map;
	int levelCount;
	std::string levelFileName;
	CommResMeth::Menu escMenu;
	sf::RectangleShape background; 
	CommResMeth::UDPSocket socket;
	std::chrono::steady_clock::time_point timeStart;
	bool isGameStart;
	int totalNumbPlayer;
	int playerNumber;

	// UI
	sf::Text playerHP;

	// Online
	float onlineLatency;
	static constexpr float synCooldown = 1.0f;
	float synTimer;
public:
	SceneBulletHell(Scene* const parent);
	~SceneBulletHell();
	CommResMeth::GameState Exec();
	void Reset();
	void Update();
	void DrawScene();
public:
	static std::set<std::shared_ptr<ObjCharacter>> layerDefault;
	static std::vector<std::shared_ptr<ObjPlayer>> layerPlayer;
	static std::set<std::shared_ptr<ObjCharacter>> layerDelete;
	static Board brd;

	// Changing the tile size require to rebuild the soluction
	static constexpr int tileWidth = 50;
	static constexpr int tileHeight = 50;
};
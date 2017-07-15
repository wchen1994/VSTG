/*
A touhou like game
*/
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <cmath>
#include <list>
#include <cstdlib>
#include <memory>

#include "Essential.hpp"
#include "Scene.hpp"
#include "SceneGame.hpp"
#include "SceneStartMenu.hpp"
#include "SceneMapEditor.h"
#include "SceneLobby.h"
#include "AssetManager.h"

#ifdef _DEBUG
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-network-d.lib")
#pragma comment(lib, "nfd_d.lib")
#else
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(lib, "sfml-network.lib")
#pragma comment(lib, "nfd.lib")
#endif


int main(){
	// For test used
	Essential::wnd.setSize(sf::Vector2u(400, 300));
	// End
	AssetManager::assetManager.GetTexture("Resources/Textures/Bullet00.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/Bullet01.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/BulletPlayer.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/BulletPlayer02.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/button01.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/Enemy01.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/Enemy02.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/Enemy03.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/menu01.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/menu02.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/Player00.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/rock0.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/rock1.png");
	AssetManager::assetManager.GetTexture("Resources/Textures/TextBox01.png");
	AssetManager::assetManager.GetSoundBuffer("Resources/Sounds/laser1.wav");
	AssetManager::assetManager.GetSoundBuffer("Resources/Sounds/laser2.wav");
	AssetManager::assetManager.GetSoundBuffer("Resources/Sounds/laser3.wav");
	AssetManager::assetManager.GetSoundBuffer("Resources/Sounds/laser4.wav");

	std::unique_ptr<Scene> pScene;
	std::list<std::unique_ptr<Scene>> lScenes;

	Essential::GameState gameState = Essential::GameState::MENU;
	Essential::textFont.loadFromFile("Resources/Fonts/msyh.ttf");
	
	lScenes.push_back(std::make_unique<SceneStartMenu>(SceneStartMenu(Essential::wnd)));

	while(!lScenes.empty()){
		gameState = (lScenes.back())->Run();
		switch (gameState){
		case Essential::GameState::POP:
			lScenes.pop_back();
			break;
		case Essential::GameState::GAME:
			Essential::isHost = false;
			Essential::isClient = false;
			Essential::playerNumber = 0;
			lScenes.push_back(std::make_unique<SceneGame>(SceneGame(Essential::wnd)));
			break;
		case Essential::GameState::EDITOR:
			lScenes.push_back(std::make_unique<SceneMapEditor>(SceneMapEditor()));
			break;
		case Essential::GameState::LOBBY:
			Essential::socket.FlushPacketQueue();
			lScenes.push_back(std::make_unique<SceneLobby>(SceneLobby()));
			break;
		case Essential::GameState::GAMEHOST:
		{
			Essential::isHost = true;
			Essential::isClient = false;
			Essential::socket.FlushPacketQueue();
			lScenes.push_back(std::make_unique<SceneGame>(SceneGame(Essential::wnd)));
			break;
		}
		case Essential::GameState::GAMECLIENT:
			Essential::isHost = false;
			Essential::isClient = true;
			Essential::socket.FlushPacketQueue();
			lScenes.push_back(std::make_unique<SceneGame>(SceneGame(Essential::wnd)));
			break;
		default:
			break;
		}
//		Essential::assetManager.killLonePtr();
	}

	return 0;
}

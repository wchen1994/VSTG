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
	std::unique_ptr<Scene> pScene;
	std::list<std::unique_ptr<Scene>> lScenes;

	Essential::GameState gameState = Essential::MENU;
	Essential::textFont.loadFromFile("Resources/Fonts/msyh.ttf");
	
	lScenes.push_back(std::make_unique<SceneStartMenu>(SceneStartMenu(Essential::wnd)));

	while(!lScenes.empty()){
		gameState = (lScenes.back())->Run();
		switch (gameState){
			case Essential::POP:
				lScenes.pop_back();
				break;
			case Essential::GAME:
				lScenes.push_back(std::make_unique<SceneGame>(SceneGame(Essential::wnd)));
				break;
			case Essential::EDITOR:
				lScenes.push_back(std::make_unique<SceneMapEditor>(SceneMapEditor()));
			default:
				break;
		}
		Essential::assetManager.killLonePtr();
	}

	return 0;
}

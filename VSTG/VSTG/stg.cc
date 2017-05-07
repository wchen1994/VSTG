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
#include "Game.hpp"
#include "StartMenu.hpp"
#include "SceneMapEditor.h"

#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(lib, "nfd_d.lib")

int main(){
	std::unique_ptr<Scene> pScene;
	std::list<std::unique_ptr<Scene>> lScenes;

	Essential::GameState gameState = Essential::MENU;

	// The drawing of font in StartMenu has been disabled
	// because it lead to assertion error while failed loading
	lScenes.push_back(std::make_unique<StartMenu>(StartMenu(Essential::wnd)));

	while(!lScenes.empty()){
		gameState = (lScenes.back())->Run();
		switch (gameState){
			case Essential::POP:
				//pScene = lScenes.back();
				//delete pScene;
				lScenes.pop_back();
				break;
			case Essential::GAME:
				Essential::isGameOver = false;
				lScenes.push_back(std::make_unique<Game>(Game(Essential::wnd)));
				break;
			case Essential::EDITOR:
				lScenes.push_back(std::make_unique<SceneMapEditor>(SceneMapEditor()));
			default:
				break;
		}
	}

//	Game mGame(Essential::wnd);
//	mGame.Run();

	return 0;
}

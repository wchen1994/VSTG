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

#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-audio.lib")

int main(){
	Scene *pScene;
	std::list<std::unique_ptr<Scene>> lScenes;

	Essential::GameState gameState = Essential::MENU;

	// Honestly I don't know why I need to break it into two statement
	StartMenu sm(Essential::wnd);
	lScenes.push_back(std::make_unique<StartMenu>(sm));

	while(!lScenes.empty()){
		gameState = (lScenes.back())->Run();
		switch (gameState){
			case Essential::POP:
				//pScene = lScenes.back();
				//delete pScene;
				lScenes.pop_back();
				break;
			case Essential::GAME:
				lScenes.push_back(std::make_unique<Game>(Game(Essential::wnd)));
				break;
			default:
				break;
		}
	}

	return 0;
}

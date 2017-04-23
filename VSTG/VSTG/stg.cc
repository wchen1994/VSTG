/*
A touhou like game
*/
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <cmath>
#include <list>
#include <cstdlib>

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
	std::list<Scene*> lScenes;

	Essential::GameState gameState = Essential::MENU;
	lScenes.push_back(new StartMenu(Essential::wnd));

	while(!lScenes.empty()){
		gameState = (lScenes.back())->Run();
		switch (gameState){
			case Essential::POP:
				pScene = lScenes.back();
				delete pScene;
				lScenes.pop_back();
				break;
			case Essential::GAME:
				lScenes.push_back(new Game(Essential::wnd));
				break;
			default:
				break;
		}
	}

	return 0;
}

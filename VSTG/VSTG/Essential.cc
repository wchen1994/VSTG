#include <iostream>
#include "Essential.hpp"

bool Essential::isGameOver = false;
bool Essential::isExit = false;
Essential::GameState Essential::gameState = GAME;
sf::RenderWindow Essential::wnd(sf::VideoMode(Essential::ScreenWidth, Essential::ScreenHeight), "Game", sf::Style::Close|sf::Style::Titlebar);
void Essential::defHandleMsg(const sf::Event &event){
	switch(event.type){
		case sf::Event::Closed:
			Essential::wnd.close();
			break;
		default:
			break;
	}
}

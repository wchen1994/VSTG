#include <iostream>
#include "Essential.hpp"


bool Essential::isGameOver = false;
bool Essential::isExit = false;
Essential::GameState Essential::gameState = GAME;
sf::RenderWindow Essential::wnd(sf::VideoMode(Essential::ScreenWidth, Essential::ScreenHeight), "Game", sf::Style::Close|sf::Style::Titlebar);
TextManager Essential::textManager("Resources/texts/zh_ch.csv");
sf::Font Essential::textFont;

void Essential::defHandleMsg(const sf::Event &event){
	switch(event.type){
		case sf::Event::Closed:
			Essential::wnd.close();
			break;
		default:
			break;
	}
}

sf::Vector2f Essential::vec2i2f(const sf::Vector2i& vec) { return sf::Vector2f(float(vec.x), float(vec.y)); }
sf::Vector2i Essential::vec2f2i(const sf::Vector2f& vec) { return sf::Vector2i(int(vec.x), int(vec.y)); }
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Essential{
public:
	static bool isGameOver;
	static bool isExit;
	enum GameState{MENU, GAME, POP};
	static GameState gameState;
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
	static sf::RenderWindow wnd;
	static void defHandleMsg(const sf::Event &eventType);
};


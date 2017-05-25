#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "TextManager.h"
#include "ResManager.h"

class Essential {
public:
	static bool isGameOver;
	static bool isExit;
	enum GameState { MENU, GAME, EDITOR, POP };
	static GameState gameState;
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
	static sf::RenderWindow wnd;
	static TextManager textManager;
	static void defHandleMsg(const sf::Event &eventType);
	static sf::Vector2f vec2i2f(const sf::Vector2i& vec);
	static sf::Vector2f vec2i2f(int& x, int& y);
	static sf::Vector2i vec2f2i(const sf::Vector2f& vec);
	static sf::Vector2i vec2f2i(float& x, float& y);
	static sf::Font textFont;
	static float textScale;
	static ResManager resManager;
	static sf::IntRect GameCanvas;
	static float windowScale;
};
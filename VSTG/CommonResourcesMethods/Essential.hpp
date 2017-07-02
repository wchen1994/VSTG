#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <set>
#include <random>
#include <chrono>

#include "TextManager.h"
#include "AssetManager.h"
#include "UDPSocket.h"

namespace CommResMeth {
		enum class GameState { MENU, GAME, EDITOR, LOBBY, POP, GAMEHOST, GAMECLIENT };

		static constexpr int ScreenWidth = 800;
		static constexpr int ScreenHeight = 600;
		static constexpr int CANVAS_TOP = 25;
		static constexpr int CANVAS_LEFT = 25;
		static constexpr int CANVAS_WIDTH = 500;
		static constexpr int CANVAS_HEIGHT = 550;

		static sf::RenderWindow wnd(sf::VideoMode(ScreenWidth, ScreenHeight), "Game", sf::Style::Default);
		static float windowScale = 1.0f;
		static sf::IntRect GameCanvass(CANVAS_TOP, CANVAS_LEFT, CANVAS_WIDTH, CANVAS_HEIGHT);
		static float textScale = 1.0;
		static std::random_device rd;
		static std::mt19937 rng(rd());
		static std::uniform_real_distribution<float> angleDist(0.0f, 180.0f);
		static std::uniform_real_distribution<float> xDist = std::uniform_real_distribution<float>(0.0f, float(CANVAS_WIDTH));
		static std::uniform_real_distribution<float> yDist = std::uniform_real_distribution<float>(0.0f, float(CANVAS_HEIGHT));
		static std::uniform_real_distribution<float> normalizedDist(0.0f, 1.0f);
		static int playerNumber = 0;
		static int totalNumbPlayer = 1;
		static bool isGameStart = false;
		static bool isExit = false;
		static GameState gameState = GameState::MENU;

		static std::chrono::time_point<std::chrono::steady_clock> timeStart;
		static sf::Font textFont;

		__VSTG_API void defHandleMsg(const sf::Event &eventType);
		static bool inGamecanvas(const sf::Vector2f & pos);
		static sf::Vector2i vec2f2i(const sf::Vector2f& vec);
		static sf::Vector2i vec2f2i(const float x, const float y);
		static sf::Vector2f vec2i2f(const sf::Vector2i& vec);
		static sf::Vector2f vec2i2f(const int x, const int y);
		static sf::Vector2f normalize(const sf::Vector2f& vec);

		template<class T>
		struct vec2Compare {
			bool operator()(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs) const {
				if (lhs.y > rhs.y) {
					return true;
				}
				else if (lhs.y == rhs.y) {
					if (lhs.x > rhs.x)
						return true;
				}
				return false;
			}
		};
		typedef std::set<sf::Vector2i, vec2Compare<int>> setVecInt;

		template<class T>
		static bool inRect(sf::Rect<T> rect, sf::Vector2<T> vec) {
			return vec.x >= rect.left && vec.x < rect.left + rect.width && vec.y >= rect.top && vec.y < rect.top + rect.height;
		}
}



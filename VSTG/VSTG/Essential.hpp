#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <set>
#include <random>
#include <chrono>

#include "TextManager.h"
#include "AssetManager.h"
#include "UDPSocket.h"

class Essential {
public:
//	static bool isGameOver;
	static bool isExit;
	enum GameState { MENU, GAME, EDITOR, LOBBY, POP, GAMEHOST, GAMECLIENT };
	static GameState gameState;
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
	static constexpr unsigned short DEFAULT_HOST_PORT = 55009;
	static constexpr unsigned short DEFAULT_CLIENT_PORT = 55010;
	static sf::RenderWindow wnd;
	static TextManager textManager;
	static void defHandleMsg(const sf::Event &eventType);
	static sf::Vector2f vec2i2f(const sf::Vector2i& vec);
	static sf::Vector2f vec2i2f(int& x, int& y);
	static sf::Vector2i vec2f2i(const sf::Vector2f& vec);
	static sf::Vector2i vec2f2i(float& x, float& y);
	static sf::Vector2f normalize(const sf::Vector2f& vec);
	static sf::Font textFont;
	static float textScale;
	static sf::IntRect GameCanvas;
	static bool inGamecanvas(const sf::Vector2f & pos);
	static float windowScale;
	static AssetManager assetManager;
	static std::random_device rd;
	static std::mt19937 rng;

	static std::uniform_real_distribution<float> angleDist;
	static std::uniform_real_distribution<float> xDist;
	static std::uniform_real_distribution<float> yDist;
	static std::uniform_real_distribution<float> normalizedDist;
public:
	template<class T>
	struct vec2Compare {
		bool operator()(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs) const {
			if (lhs.y > rhs.y) {
				return true;
			}
			else if (lhs.y == rhs.y){
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

	static UDPSocket socket;
	static bool isHost;
	static bool isClient;
	static int playerNumber;
	static int totalNumbPlayer;
	static bool isGameStart;
	static std::chrono::time_point<std::chrono::steady_clock> timeStart;
	enum class PacketType : int {ADD, REMOVE, SIGNAL, SIGNAL_SIZE, CHANGE, ADD_T, CHANGE_T, COUNT};
};



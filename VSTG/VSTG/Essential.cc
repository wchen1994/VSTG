#include <iostream>
#include "Essential.hpp"
#include <cstdlib>


//bool Essential::isGameOver = false;
bool Essential::isExit = false;
sf::RenderWindow Essential::wnd(sf::VideoMode(Essential::ScreenWidth, Essential::ScreenHeight), "Game", sf::Style::Default);
TextManager Essential::textManager("Resources/texts/zh_ch.csv");
//AssetManager Essential::assetManager;
sf::Font Essential::textFont;
float Essential::textScale = 1.0;
sf::IntRect Essential::GameCanvas(25, 25, 500, 550);
float Essential::windowScale = 1.0f;
std::random_device Essential::rd;
std::mt19937 Essential::rng(rd());
std::uniform_real_distribution<float> Essential::angleDist(0.0f, 180.0f);
std::uniform_real_distribution<float> Essential::xDist(0.0f, float(GameCanvas.width));
std::uniform_real_distribution<float> Essential::yDist(0.0f, float(GameCanvas.height));
std::uniform_real_distribution<float> Essential::normalizedDist(0.0f, 1.0f);

void Essential::defHandleMsg(const sf::Event &event){
	switch(event.type){
		case sf::Event::Closed:
			Essential::wnd.close();
			break;
		case sf::Event::Resized:
			windowScale = std:: max<float>(event.size.height/600.0f, event.size.width/800.0f);
			if (windowScale > 0.5) {
				Essential::wnd.setSize(sf::Vector2u(int(800 * windowScale), int(600 * windowScale)));
			}
			else {
				Essential::wnd.setSize(sf::Vector2u(400, 300 ));
			}
			break;
		default:
			break;
	}
}

sf::Vector2f Essential::vec2i2f(const sf::Vector2i& vec) { return sf::Vector2f(float(vec.x), float(vec.y)); }
sf::Vector2f Essential::vec2i2f(int & x, int & y) { return sf::Vector2f(float(x), float(y)); }
sf::Vector2i Essential::vec2f2i(const sf::Vector2f& vec) { return sf::Vector2i(int(vec.x), int(vec.y)); }
sf::Vector2i Essential::vec2f2i(float & x, float & y) { return sf::Vector2i(int(x), int(y)); }

sf::Vector2f Essential::normalize(const sf::Vector2f & vec)
{
	float sqlen = vec.x * vec.x + vec.y * vec.y;
	return sf::Vector2f(vec.x / sqrt(sqlen), vec.y / sqrt(sqlen));
}

bool Essential::inGamecanvas(const sf::Vector2f & pos)
{
	sf::Vector2f topLeft = Essential::vec2i2f(Essential::GameCanvas.left, Essential::GameCanvas.top);
	sf::Vector2f botRight = topLeft + Essential::vec2i2f(Essential::GameCanvas.width, Essential::GameCanvas.height);
	return pos.x >= topLeft.x && pos.y >= topLeft.y && pos.x < botRight.x && pos.y < botRight.y;
}


UDPSocket Essential::socket;
bool Essential::isHost = false;
bool Essential::isClient = false;
int Essential::playerNumber = 0;
int Essential::totalNumbPlayer = 1;
bool Essential::isGameStart = false;
std::chrono::time_point<std::chrono::steady_clock> Essential::timeStart;
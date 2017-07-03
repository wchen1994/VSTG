#include <iostream>
#include "Essential.hpp"
#include <cstdlib>

namespace CommResMeth {

	void CommResMeth::defHandleMsg(sf::Window &wnd, const sf::Event &event) {
		switch (event.type) {
		case sf::Event::Closed:
			wnd.close();
			break;
		case sf::Event::Resized:
			windowScale = std::max<float>(event.size.height / 600.0f, event.size.width / 800.0f);
			if (windowScale > 0.5) {
				wnd.setSize(sf::Vector2u(int(800 * windowScale), int(600 * windowScale)));
			}
			else {
				wnd.setSize(sf::Vector2u(400, 300));
			}
			break;
		default:
			break;
		}
	}

	sf::Vector2f vec2i2f(const sf::Vector2i& vec) { return sf::Vector2f(float(vec.x), float(vec.y)); }
	sf::Vector2f vec2i2f(const int x, const int y) { return sf::Vector2f(float(x), float(y)); }
	sf::Vector2i vec2f2i(const sf::Vector2f& vec) { return sf::Vector2i(int(vec.x), int(vec.y)); }
	sf::Vector2i vec2f2i(const float x, const float y) { return sf::Vector2i(int(x), int(y)); }

	sf::Vector2f normalize(const sf::Vector2f & vec)
	{
		float sqlen = vec.x * vec.x + vec.y * vec.y;
		return sf::Vector2f(vec.x / sqrt(sqlen), vec.y / sqrt(sqlen));
	}

	bool inGamecanvas(const sf::Vector2f & pos)
	{
		sf::Vector2f topLeft = vec2i2f(CANVAS_LEFT, CANVAS_TOP);
		sf::Vector2f botRight = topLeft + vec2i2f(CANVAS_WIDTH, CANVAS_HEIGHT);
		return pos.x >= topLeft.x && pos.y >= topLeft.y && pos.x < botRight.x && pos.y < botRight.y;
	}
}
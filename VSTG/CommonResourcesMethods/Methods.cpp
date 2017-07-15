#include "Methods.h"
#include <cstdlib>
#include <iostream>

namespace CommResMeth {

	void CommResMeth::defHandleMsg(sf::RenderWindow &wnd, const sf::Event &event) {
		switch (event.type) {
		case sf::Event::Closed:
			wnd.close();
			break;
		case sf::Event::Resized:
		{
			resetWindowView(wnd);
//			windowScale = std::max<float>(event.size.height / 600.0f, event.size.width / 800.0f);
//			if (windowScale > 0.5) {
//				wnd.setSize(sf::Vector2u(int(800 * windowScale), int(600 * windowScale)));
//			}
//			else {
//				wnd.setSize(sf::Vector2u(400, 300));
//			}
			break;
		}
		default:
			break;
		}
	}

	__VSTG_API void resetWindowView(sf::RenderWindow & wnd)
	{
		sf::View view;
		resetWindowView(wnd, view);
		wnd.setView(view);
	}

	__VSTG_API void resetWindowView(const sf::RenderWindow & wnd, sf::View & view_out)
	{
		view_out.setCenter(sf::Vector2f(DEFAULT_WINDOWS_WIDTH/2, DEFAULT_WINDOWS_HEIGHT/2));
		view_out.setSize(sf::Vector2f(DEFAULT_WINDOWS_HEIGHT * getAspectRatio(wnd), DEFAULT_WINDOWS_HEIGHT));
	}

	__VSTG_API float getAspectRatio(const sf::Window & wnd)
	{
		return float(wnd.getSize().x) / float(wnd.getSize().y);
	}

	__VSTG_API float getWndScale(const sf::Window & wnd)
	{
		return (float)wnd.getSize().y / DEFAULT_WINDOWS_HEIGHT;
	}

	__VSTG_API sf::Vector2f getUnscaledCoord(const sf::Window& wnd, const sf::Vector2f & pos)
	{
		const float xOffset = (wnd.getSize().x - wnd.getSize().y * 800 / 600.f) / 2;
		sf::Vector2f vec = { pos.x - xOffset, pos.y };
		vec /= getWndScale(wnd);
		return vec;
	}

	__VSTG_API sf::Vector2i getUnscaledCoord(const sf::Window & wnd, const sf::Vector2i & pos)
	{
		sf::Vector2f vec = getUnscaledCoord(wnd, sf::Vector2f((float)pos.x, (float)pos.y));
		return sf::Vector2i((int)vec.x, (int)vec.y);
	}

	sf::Vector2f vec2i2f(const sf::Vector2i& vec) { return sf::Vector2f(float(vec.x), float(vec.y)); }
	sf::Vector2f vec2i2f(const int x, const int y) { return sf::Vector2f(float(x), float(y)); }
	sf::Vector2i vec2f2i(const sf::Vector2f& vec) { return sf::Vector2i(int(vec.x), int(vec.y)); }
	sf::Vector2i vec2f2i(const float x, const float y) { return sf::Vector2i(int(x), int(y)); }

	bool inGamecanvas(const sf::Vector2f & pos)
	{
		sf::Vector2f topLeft = vec2i2f(CANVAS_LEFT, CANVAS_TOP);
		sf::Vector2f botRight = topLeft + vec2i2f(CANVAS_WIDTH, CANVAS_HEIGHT);
		return pos.x >= topLeft.x && pos.y >= topLeft.y && pos.x < botRight.x && pos.y < botRight.y;
	}
}
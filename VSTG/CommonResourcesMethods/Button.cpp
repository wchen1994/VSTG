#include "Button.h"

namespace CommResMeth {

	Button::Button(Scene* const parent)
		: Scene(parent), pTex(nullptr)
	{
		state = ButtonState::Idle;
	}

	void Button::setTexture(const sf::String & tex)
	{
		pTex = AssetManager::GetTexture(tex);
	}

	void Button::setSprites(const sf::Vector2i & ipos, const sf::Vector2i & ppos, const sf::Vector2i & fpos, const sf::Vector2i & size)
	{
		sf::Vector2i pos[3];
		pos[0] = ipos;
		pos[1] = ppos;
		pos[2] = fpos;
		for (int i = 0; i < 3; i++) {
			sprites[i].setTexture(*pTex);
			sprites[i].setTextureRect(sf::IntRect(pos[i], size));
		}
		width = size.x;
		height = size.y;
	}

	void Button::setLable(const sf::String & s) {
		pFont = AssetManager::GetFont("Resources/Fonts/msyh.ttf");
		text.setFont(*pFont);
		text.setString(s);
		text.setCharacterSize(uint32_t(30 * textScale));
		text.setFillColor(sf::Color::White);
	}

	void Button::setPosition(int x, int y)
	{
		for (auto &sprite : sprites) {
			sprite.setPosition(float(x), float(y));
		}
		text.setPosition(float(x), float(y));
		Scene::setPosition(x, y);
	}

	void Button::Update()
	{
		sf::Vector2i vec = sf::Mouse::getPosition(*wnd);
		if (contains(CommResMeth::getUnscaledCoord(*wnd, vec))) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				state = ButtonState::Push;
			}
			else {
				if (state == ButtonState::Push)
					state = ButtonState::Release;
				else
					state = ButtonState::Focus;
			}
		}
		else {
			state = ButtonState::Idle;
		}
	}

	void Button::draw(sf::RenderTarget & gfx)
	{
		switch (state) {
		case ButtonState::Idle:
		case ButtonState::Release:
			gfx.draw(sprites[0]);
			break;
		case ButtonState::Push:
			gfx.draw(sprites[1]);
			break;
		case ButtonState::Focus:
			gfx.draw(sprites[2]);
			break;
		default:
			gfx.draw(sprites[0]);
		}
		gfx.draw(text);
	}

	Button* Button::processDefaultButton(Button* const but, const sf::String & lable, ButtonStyle style = Button::SMALL)
	{
		switch (style) {
		case Button::SMALL:
			but->setTexture("Resources/Textures/button01.png");
			but->setLable(lable);
			but->setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
			break;
		case Button::MEDIUM:
			but->setTexture("Resources/Textures/button01.png");
			but->setLable(lable);
			but->setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(150, 50));
			break;
		default:
			but->setTexture("Resources/Textures/button01.png");
			but->setLable(lable);
			but->setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		}

		return but;
	}
}
#include "Button.h"

namespace CommResMeth {

	Button::Button(Scene* const parent, const sf::Vector2i & pos, ButtonStyle style, const sf::String & label)
		: Scene(parent), pTex(nullptr), state(ButtonState::Idle)
	{
		setPosition(pos);
		setStyle(style, label);
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
		setSize(size);
	}

	void Button::setLable(const sf::String & s) {
		pFont = AssetManager::GetFont("Resources/Fonts/msyh.ttf");
		text.setFont(*pFont);
		text.setString(s);
		text.setCharacterSize(uint32_t(30 * textScale));
		text.setFillColor(sf::Color::White);
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

	void Button::Draw()
	{
		switch (state) {
			case ButtonState::Idle:
			case ButtonState::Release:
				wnd->draw(sprites[0]);
				break;
			case ButtonState::Push:
				wnd->draw(sprites[1]);
				break;
			case ButtonState::Focus:
				wnd->draw(sprites[2]);
				break;
			default:
				wnd->draw(sprites[0]);
			}
			wnd->draw(text);
	}

	void Button::setStyle(ButtonStyle style, const sf::String & lable)
	{
		switch (style) {
		case Button::MEDIUM:
			setTexture("Resources/Textures/button01.png");
			setLable(lable);
			setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(150, 50));
			break;
		case Button::SMALL:
		default:
			setTexture("Resources/Textures/button01.png");
			setLable(lable);
			setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
			break;
		}
		sceneView.setCenter(width / 2.f, height / 2.f);
		sceneView.setSize((float)width, (float)height);
	}
}
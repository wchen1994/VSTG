#include "Button.h"
#include "Essential.hpp"

Button::Button()
: pTex(nullptr) 
{ 
	state = ButtonState::Idle;
}

void Button::setSprites(const sf::Vector2i & ipos, const sf::Vector2i & ppos, const sf::Vector2i & fpos, const sf::Vector2i & size)
{
	sf::Vector2i pos[3];
	pos[0] = ipos;
	pos[1] = ppos;
	pos[2] = fpos;
	this->setSprites(pos, size);
}

void Button::setSprites(const sf::Vector2i pos[], const sf::Vector2i & size)
{
	pTex = AssetManager::assetManager.GetTexture(textureName);
	for (int i = 0; i < 3; i++) {
		sprites[i].setTexture(*pTex);
		sprites[i].setTextureRect(sf::IntRect(pos[i], size));
	}
	this->size.x = size.x;
	this->size.y = size.y;
	text.setFont(Essential::textFont);
	text.setString(lable.toWideString());
	text.setCharacterSize(uint32_t(30 * Essential::textScale));
	text.setFillColor(sf::Color::White);
}

void Button::setPosition(const sf::Vector2f & pos)
{
	for (auto &sprite : sprites) {
		sprite.setPosition(pos);
	}
	text.setPosition(pos);
	position = pos;
}

void Button::Update()
{
	sf::Vector2i vecI = sf::Mouse::getPosition(Essential::wnd);
	sf::Vector2f vecF = { float(vecI.x), float(vecI.y) };
	vecF /= Essential::windowScale;
	if (vecF.x > position.x && vecF.x < position.x + size.x &&
		vecF.y > position.y && vecF.y < position.y + size.y) {
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

void Button::Draw(sf::RenderTarget & gfx)
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

void Button::SettingDefaultButton(Button & but, sf::String lable, ButtonStyle style = Button::SMALL)
{
	switch (style) {
	case Button::SMALL:
		but.setTexture("Resources/Textures/button01.png");
		but.setLable(lable);
		but.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		break;
	case Button::MEDIUM:
		but.setTexture("Resources/Textures/button01.png");
		but.setLable(lable);
		but.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(150, 50));
		break;
	default:
		but.setTexture("Resources/Textures/button01.png");
		but.setLable(lable);
		but.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
	}
}

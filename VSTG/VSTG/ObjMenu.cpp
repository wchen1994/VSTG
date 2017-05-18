#include "ObjMenu.h"
#include "Essential.hpp"

ObjMenu::ObjMenu(sf::IntRect rect, sf::String title, uint32_t flag) : hasInit(false)
{
	this->flag = flag;
	menuTexture = Essential::resManager.GetRes("Resources/Textures/menu01.png");
	butTexture = Essential::resManager.GetRes("Resources/Textures/button01.png"); //Can not load texture
//	butTexture = std::make_shared<sf::Texture>(sf::Texture());
//	butTexture->loadFromFile("Resources/Textures/button02.png");
	bg.setTexture(*menuTexture);
	bg.setPosition(float(rect.left), float(rect.top));
	bg.setTextureRect(sf::IntRect(0, 0, rect.width, rect.height));
	this->title = title;
	text.setString(title);
	text.setPosition(float(rect.left), float(rect.top));
	text.setFont(Essential::textFont);
	
	this->rect = rect;

}

void ObjMenu::Init()
{
	switch (flag) {
	case MENUFLAG::OK:
		but1.setTexture(*butTexture);
		but1.setLable("OK");
		but1.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		but1.setPosition(sf::Vector2f(float(rect.left + rect.width / 2), float(rect.top + rect.height / 2)));
		break;
	case MENUFLAG::OK_CANCEL:
		but1.setTexture(*butTexture);
		but1.setLable("OK");
		but1.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		but1.setPosition(sf::Vector2f(float(rect.left), float(rect.top + rect.height / 2)));
		but2.setTexture(*butTexture);
		but2.setLable("CANCEL");
		but2.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		but2.setPosition(sf::Vector2f(float(rect.left + rect.width / 2), float(rect.top + rect.height / 2)));
		break;
	case MENUFLAG::YES_NO:
		but1.setTexture(*butTexture);
		but1.setLable("YES");
		but1.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		but1.setPosition(sf::Vector2f(float(rect.left), float(rect.top + rect.height / 2)));
		but2.setTexture(*butTexture);
		but2.setLable("NO");
		but2.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		but2.setPosition(sf::Vector2f(float(rect.left + rect.width / 2), float(rect.top + rect.height / 2)));
		break;
	}
	hasInit = true;
}

uint32_t ObjMenu::MenuUpdate()
{
	if (!hasInit)
		Init();
	switch (flag) {
	case MENUFLAG::OK:
		but1.Update();
		if (but1.getStatus() == Button::ButtonState::Push)
			return 1;
		break;
	case MENUFLAG::OK_CANCEL:
	case MENUFLAG::YES_NO:
		but1.Update();
		but2.Update();
		if (but1.getStatus() == Button::ButtonState::Push)
			return 1;
		if (but2.getStatus() == Button::ButtonState::Push)
			return 2;
		break;
	}
	return 0;
}

void ObjMenu::Draw(sf::RenderTarget & gfx)
{
	gfx.draw(bg);
	gfx.draw(text);
	switch (flag) {
	case MENUFLAG::OK:
		but1.Draw(gfx);
		break;
	case MENUFLAG::OK_CANCEL:
	case MENUFLAG::YES_NO:
		but1.Draw(gfx);
		but2.Draw(gfx);
		break;
	}
}

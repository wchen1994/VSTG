#include "ObjMenu.h"
#include "Essential.hpp"

ObjMenu::ObjMenu(sf::IntRect rect, sf::String title, uint32_t flag)
{
	this->flag = flag;
	pBG = Essential::assetManager.GetTexture("Resources/Textures/menu01.png");
	bg.setTexture(*pBG);
	bg.setPosition(float(rect.left), float(rect.top));
	bg.setTextureRect(sf::IntRect(0, 0, rect.width, rect.height));
	this->title = title;
	text.setString(title);
	text.setPosition(float(rect.left), float(rect.top));
	text.setFont(Essential::textFont);
	
	this->rect = rect;

	switch (flag) {
	case MENUFLAG::OK:
//		but1.setTexture("Resources/Textures/button01.png");
//		but1.setLable(Essential::textManager.getText(7));
//		but1.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		Button::SettingDefaultButton(but1, Essential::textManager.getText(7), Button::SMALL);
		but1.setPosition(sf::Vector2f(float(rect.left + rect.width / 2), float(rect.top + rect.height / 2)));
		break;
	case MENUFLAG::OK_CANCEL:
//		but1.setTexture("Resources/Textures/button01.png");
//		but1.setLable(Essential::textManager.getText(7));
//		but1.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		Button::SettingDefaultButton(but1, Essential::textManager.getText(7), Button::SMALL);
		but1.setPosition(sf::Vector2f(float(rect.left), float(rect.top + rect.height / 2)));
//		but2.setTexture("Resources/Textures/button01.png");
//		but2.setLable(Essential::textManager.getText(8));
//		but2.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		Button::SettingDefaultButton(but2, Essential::textManager.getText(8), Button::SMALL);
		but2.setPosition(sf::Vector2f(float(rect.left + rect.width / 2), float(rect.top + rect.height / 2)));
		break;
	case MENUFLAG::YES_NO:
//		but1.setTexture("Resources/Textures/button01.png");
//		but1.setLable(Essential::textManager.getText(5));
//		but1.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		Button::SettingDefaultButton(but1, Essential::textManager.getText(5), Button::SMALL);
		but1.setPosition(sf::Vector2f(float(rect.left), float(rect.top + rect.height / 2)));
//		but2.setTexture("Resources/Textures/button01.png");
//		but2.setLable(Essential::textManager.getText(6));
//		but2.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(90, 40));
		Button::SettingDefaultButton(but2, Essential::textManager.getText(6), Button::SMALL);
		but2.setPosition(sf::Vector2f(float(rect.left + rect.width / 2), float(rect.top + rect.height / 2)));
		break;
	}
}

uint32_t ObjMenu::MenuUpdate()
{
	switch (flag) {
	case MENUFLAG::OK:
		but1.Update();
		if (but1.getStatus() == Button::ButtonState::Release)
			return 1;
		break;
	case MENUFLAG::OK_CANCEL:
	case MENUFLAG::YES_NO:
		but1.Update();
		but2.Update();
		if (but1.getStatus() == Button::ButtonState::Release)
			return 1;
		if (but2.getStatus() == Button::ButtonState::Release)
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

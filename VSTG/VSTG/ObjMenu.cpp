#include "ObjMenu.h"
#include "Essential.hpp"

ObjMenu::ObjMenu(sf::IntRect rect, sf::String title, uint32_t flag)
{
	this->flag = flag;
	pBG = AssetManager::assetManager.GetTexture("Resources/Textures/menu01.png");

	bg.setTexture(*pBG);
	bg.setTextureRect(sf::IntRect(padding, padding, rect.width, rect.height));
	bg.setPosition(float(rect.left), float(rect.top));
	
	horiBar.setTexture(*pBG);
	horiBar.setTextureRect(sf::IntRect(padding, 0, rect.width, padding));
	horiBar.setOrigin(rect.width / 2.0f, padding + rect.height / 2.0f);
	horiBar.setPosition(float(rect.left + rect.width / 2.0f), float(rect.top + rect.height / 2.0f));

	vertBar.setTexture(*pBG);
	vertBar.setTextureRect(sf::IntRect(0, padding, padding, rect.height));
	vertBar.setOrigin(padding + rect.width / 2.0f, rect.height / 2.0f);
	vertBar.setPosition(float(rect.left + rect.width / 2.0f), float(rect.top + rect.height / 2.0f));

	corner.setTexture(*pBG);
	corner.setTextureRect(sf::IntRect(0, 0, padding, padding));
	corner.setOrigin(padding + rect.width / 2.0f, padding + rect.height / 2.0f);
	corner.setPosition(float(rect.left + rect.width / 2.0f), float(rect.top + rect.height / 2.0f));
	

	this->title = title;
	text.setString(title);
	text.setPosition(float(rect.left), float(rect.top));
	text.setFont(Essential::textFont);
	
	this->rect = rect;

	switch (flag) {
	case MENUFLAG::OK:
		Button::SettingDefaultButton(but1, Essential::textManager.getText(7), Button::SMALL);
		but1.setPosition(sf::Vector2f(float(rect.left + rect.width / 2), float(rect.top + rect.height / 2)));
		break;
	case MENUFLAG::OK_CANCEL:
		Button::SettingDefaultButton(but1, Essential::textManager.getText(7), Button::SMALL);
		but1.setPosition(sf::Vector2f(float(rect.left), float(rect.top + rect.height / 2)));

		Button::SettingDefaultButton(but2, Essential::textManager.getText(8), Button::SMALL);
		but2.setPosition(sf::Vector2f(float(rect.left + rect.width / 2), float(rect.top + rect.height / 2)));
		break;
	case MENUFLAG::YES_NO:
		Button::SettingDefaultButton(but1, Essential::textManager.getText(5), Button::SMALL);
		but1.setPosition(sf::Vector2f(float(rect.left), float(rect.top + rect.height / 2)));

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

	gfx.draw(horiBar);
	horiBar.setScale(1.0f, -1.0f);
	gfx.draw(horiBar);
	horiBar.setScale(1.0f, 1.0f);

	gfx.draw(vertBar);
	vertBar.setScale(-1.0f, 1.0f);
	gfx.draw(vertBar);
	vertBar.setScale(1.0f, 1.0f);

	gfx.draw(corner);
	corner.setScale(-1.0f, 1.0f);
	gfx.draw(corner);
	corner.setScale(1.0f, -1.0f);
	gfx.draw(corner);
	corner.setScale(-1.0f, -1.0f);
	gfx.draw(corner);
	corner.setScale(1.0f, 1.0f);
	
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


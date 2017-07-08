#include "Menu.h"

namespace CommResMeth {

	Menu::Menu(sf::IntRect rect, sf::String title, uint32_t flag, Scene* const parent) :
		Scene(parent), but1(this), but2(this), but3(this)
	{
		this->flag = flag;
		pBG = AssetManager::GetTexture("Resources/Textures/menu01.png");

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
		pFont = AssetManager::GetFont("Resources/Fonts/msyh.ttf");
		text.setString(title);
		text.setPosition(float(rect.left), float(rect.top));
		text.setFont(*pFont);

		this->rect = rect;

		switch (flag) {
		case MENUFLAG::OK:
			but1.setStyle(Button::SMALL, TextManager::getText(7));
			but1.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
			break;
		case MENUFLAG::OK_CANCEL:
			but1.setStyle(Button::SMALL, TextManager::getText(7));
			but1.setPosition(rect.left, rect.top + rect.height / 2);

			but2.setStyle(Button::SMALL, TextManager::getText(8));
			but2.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
			break;
		case MENUFLAG::YES_NO:
			but1.setStyle(Button::SMALL, TextManager::getText(5));
			but1.setPosition(rect.left, rect.top + rect.height / 2);

			but2.setStyle(Button::SMALL, TextManager::getText(6));
			but2.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
			break;
		}
	}

	uint32_t Menu::MenuUpdate()
	{
		switch (flag) {
		case MENUFLAG::OK:
			but1.update();
			if (but1.getStatus() == Button::ButtonState::Release)
				return 1;
			break;
		case MENUFLAG::OK_CANCEL:
		case MENUFLAG::YES_NO:
			but1.update();
			but2.update();
			if (but1.getStatus() == Button::ButtonState::Release)
				return 1;
			if (but2.getStatus() == Button::ButtonState::Release)
				return 2;
			break;
		}
		return 0;
	}

	void Menu::draw(sf::RenderTarget & gfx)
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
			but1.draw();
			break;
		case MENUFLAG::OK_CANCEL:
		case MENUFLAG::YES_NO:
			but1.draw();
			but2.draw();
			break;
		}
	}

}
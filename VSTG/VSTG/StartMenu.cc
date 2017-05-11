#include "StartMenu.hpp"
#include "Essential.hpp"
#include <assert.h>

StartMenu::StartMenu(sf::RenderWindow& wnd)
:
wnd(wnd)
{
	butTexture.loadFromFile("Resources/Textures/button01.png");
}

Essential::GameState StartMenu::Run(){

	but.setTexture(butTexture);
//	but.setLable(L"¿ªÊ¼ÓÎÏ·");
	but.setLable(Essential::textManager.getText(0));
	but.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 50), sf::Vector2i(100, 50));

	while(wnd.isOpen()){
		while(wnd.pollEvent(event)){
			switch(event.type){
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Return){
						return Essential::GAME;
					}
					if (event.key.code == sf::Keyboard::E) {
						return Essential::EDITOR;
					}
					break;
				default:
					Essential::defHandleMsg(event);
			}
		}

		but.Update();

		if (but.getStatus() == Button::ButtonState::Push) {
			Essential::isGameOver = false;
			return Essential::GAME;
		}

		wnd.clear(sf::Color(100,255,255));
		but.Draw(wnd);
		wnd.display();
	}
	return Essential::POP;
}

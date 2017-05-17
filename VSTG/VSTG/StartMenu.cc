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

	butStart.setTexture(butTexture);
	butStart.setLable(Essential::textManager.getText(0));
	butStart.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(150, 50));
	butStart.setPosition(sf::Vector2f(550.0, 340.0));
	butEdit.setTexture(butTexture);
	butEdit.setLable(Essential::textManager.getText(1));
	butEdit.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(150, 50));
	butEdit.setPosition(sf::Vector2f(550.0, 400.0));
	butExit.setTexture(butTexture);
	butExit.setLable(Essential::textManager.getText(2));
	butExit.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(150, 50));
	butExit.setPosition(sf::Vector2f(550.0, 460.0));

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

		// Button Update
		butStart.Update();
		butEdit.Update();
		butExit.Update();

		// Button Handle
		if (butStart.getStatus() == Button::ButtonState::Push) {
			return Essential::GAME;
		}
		if (butEdit.getStatus() == Button::ButtonState::Push) {
			return Essential::EDITOR;
		}
		if (butExit.getStatus() == Button::ButtonState::Push) {
			return Essential::POP;
		}

		wnd.clear(sf::Color(100,255,255));
		butStart.Draw(wnd);
		butEdit.Draw(wnd);
		butExit.Draw(wnd);
		wnd.display();
	}
	return Essential::POP;
}

#include "SceneStartMenu.hpp"
#include "Essential.hpp"
#include <assert.h>

SceneStartMenu::SceneStartMenu(sf::RenderWindow& wnd)
:
wnd(wnd)
{
	butStart.setTexture("Resources/Textures/button01.png");
	butStart.setLable(Essential::textManager.getText(1));
	butStart.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(150, 50));
	butStart.setPosition(sf::Vector2f(550.0, 340.0));

	butEdit.setTexture("Resources/Textures/button01.png");
	butEdit.setLable(Essential::textManager.getText(2));
	butEdit.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(150, 50));
	butEdit.setPosition(sf::Vector2f(550.0, 400.0));

	butExit.setTexture("Resources/Textures/button01.png");
	butExit.setLable(Essential::textManager.getText(3));
	butExit.setSprites(sf::Vector2i(0, 0), sf::Vector2i(0, 110), sf::Vector2i(0, 51), sf::Vector2i(150, 50));
	butExit.setPosition(sf::Vector2f(550.0, 460.0));
}

Essential::GameState SceneStartMenu::Run(){

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
				case sf::Event::GainedFocus:
					isFocus = true;
					break;
				case sf::Event::LostFocus:
					isFocus = false;
				default:
					Essential::defHandleMsg(event);
			}
		}

		if (isFocus) {
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
		}

		wnd.clear(sf::Color(100,255,255));
		butStart.Draw(wnd);
		butEdit.Draw(wnd);
		butExit.Draw(wnd);
		wnd.display();
	}
	return Essential::POP;
}

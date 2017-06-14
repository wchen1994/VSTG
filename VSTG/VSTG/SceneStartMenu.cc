#include "SceneStartMenu.hpp"
#include "Essential.hpp"
#include <assert.h>

SceneStartMenu::SceneStartMenu(sf::RenderWindow& wnd)
:
wnd(wnd), isFocus(true)
{
	Button::SettingDefaultButton(butStart, Essential::textManager.getText(1), Button::MEDIUM);
	butStart.setPosition(sf::Vector2f(550.0, 340.0));

	Button::SettingDefaultButton(butEdit, Essential::textManager.getText(2), Button::MEDIUM);
	butEdit.setPosition(sf::Vector2f(550.0, 400.0));

	Button::SettingDefaultButton(butExit, Essential::textManager.getText(3), Button::MEDIUM);
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
			if (butStart.getStatus() == Button::ButtonState::Release) {
				return Essential::GAME;
			}
			if (butEdit.getStatus() == Button::ButtonState::Release) {
				return Essential::EDITOR;
			}
			if (butExit.getStatus() == Button::ButtonState::Release) {
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

#include "SceneStartMenu.hpp"
#include "Essential.hpp"
#include <assert.h>

SceneStartMenu::SceneStartMenu(sf::RenderWindow& wnd)
:
wnd(wnd), isFocus(true)
{
	CommResMeth::Button::SettingDefaultButton(butStart, CommResMeth::TextManager::getText(1), CommResMeth::Button::MEDIUM);
	butStart.setPosition(sf::Vector2f(550.0, 280.0));

	CommResMeth::Button::SettingDefaultButton(butOnline, "Start Online", CommResMeth::Button::MEDIUM);
	butOnline.setPosition(sf::Vector2f(550.0, 340.0));

	CommResMeth::Button::SettingDefaultButton(butEdit, CommResMeth::TextManager::getText(2), CommResMeth::Button::MEDIUM);
	butEdit.setPosition(sf::Vector2f(550.0, 400.0));

	CommResMeth::Button::SettingDefaultButton(butExit, CommResMeth::TextManager::getText(3), CommResMeth::Button::MEDIUM);
	butExit.setPosition(sf::Vector2f(550.0, 460.0));
}

CommResMeth::GameState SceneStartMenu::Run(){

	while(wnd.isOpen()){
		while(wnd.pollEvent(event)){
			switch(event.type){
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Return){
						return CommResMeth::GameState::GAME;
					}
					if (event.key.code == sf::Keyboard::E) {
						return CommResMeth::GameState::EDITOR;
					}
					break;
				case sf::Event::GainedFocus:
					isFocus = true;
					break;
				case sf::Event::LostFocus:
					isFocus = false;
				default:
					CommResMeth::defHandleMsg(event);
			}
		}

		if (isFocus) {
			// Button Update
			butStart.Update();
			butOnline.Update();
			butEdit.Update();
			butExit.Update();

			// Button Handle
			if (butStart.getStatus() == CommResMeth::Button::ButtonState::Release) {
				return CommResMeth::GameState::GAME;
			}
			if (butOnline.getStatus() == CommResMeth::Button::ButtonState::Release) {
				return CommResMeth::GameState::LOBBY;
			}
			if (butEdit.getStatus() == CommResMeth::Button::ButtonState::Release) {
				return CommResMeth::GameState::EDITOR;
			}
			if (butExit.getStatus() == CommResMeth::Button::ButtonState::Release) {
				return CommResMeth::GameState::POP;
			}
		}

		wnd.clear(sf::Color(100,255,255));
		butStart.Draw(wnd);
		butOnline.Draw(wnd);
		butEdit.Draw(wnd);
		butExit.Draw(wnd);
		wnd.display();
	}
	return CommResMeth::GameState::POP;
}

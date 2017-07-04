#include "SceneStartMenu.hpp"
#include <assert.h>

namespace DllSceneStartMenu {

	SceneStartMenu::SceneStartMenu(Scene* const parent)
		:
		Scene(parent), isFocus(true),
		butStart(this), butOnline(this), butEdit(this), butExit(this)
	{
		CommResMeth::Button::processDefaultButton(&butStart, CommResMeth::TextManager::getText(1), CommResMeth::Button::MEDIUM);
		butStart.setPosition(550, 280);

		CommResMeth::Button::processDefaultButton(&butOnline, "Start Online", CommResMeth::Button::MEDIUM);
		butOnline.setPosition(550, 340);

		CommResMeth::Button::processDefaultButton(&butEdit, CommResMeth::TextManager::getText(2), CommResMeth::Button::MEDIUM);
		butEdit.setPosition(550, 400);

		CommResMeth::Button::processDefaultButton(&butExit, CommResMeth::TextManager::getText(3), CommResMeth::Button::MEDIUM);
		butExit.setPosition(550, 460);
	}

	CommResMeth::GameState SceneStartMenu::Exec() {

		while (wnd->isOpen()) {
			while (wnd->pollEvent(event)) {
				switch (event.type) {
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Return) {
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
					CommResMeth::defHandleMsg(*wnd, event);
				}
			}

			if (isFocus) {
				// Button Update
				butStart.update();
				butOnline.update();
				butEdit.update();
				butExit.update();

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
			wnd->clear(sf::Color(100, 255, 255));
			butStart.draw(*wnd);
			butOnline.draw(*wnd);
			butEdit.draw(*wnd);
			butExit.draw(*wnd);
			wnd->display();
		}
		return CommResMeth::GameState::POP;
	}
}
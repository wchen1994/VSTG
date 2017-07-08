#include "SceneStartMenu.h"
#include <assert.h>

namespace DllSceneStartMenu {

	SceneStartMenu::SceneStartMenu(Scene* const parent)
		:
		Scene(parent), isFocus(true), isFullscreen(false),
		butStart(this, { 550,280 }, CommResMeth::Button::MEDIUM, CommResMeth::TextManager::getText(1)),
		butOnline(this, { 550,340 }, CommResMeth::Button::MEDIUM, "Start Online"),
		butEdit(this, { 550,400 }, CommResMeth::Button::MEDIUM, CommResMeth::TextManager::getText(2)),
		butExit(this, { 550,460 }, CommResMeth::Button::MEDIUM, CommResMeth::TextManager::getText(3))
	{
	}

	int SceneStartMenu::Exec() {

		while (wnd->isOpen()) {
			while (wnd->pollEvent(event)) {
				switch (event.type) {
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Return) {
						if (event.key.system) {
							isFullscreen = !isFullscreen;
							if (!isFullscreen)
								wnd->create(sf::VideoMode::getDesktopMode(), "Game", sf::Style::Default);
							else
								wnd->create(sf::VideoMode::getFullscreenModes()[0], "Game", sf::Style::Fullscreen);
							CommResMeth::resetWindowView(*wnd);
						}
						else
							return GAMESTATE_GAME_OFFLINE;
					}
					if (event.key.code == sf::Keyboard::E) {
						return GAMESTATE_EDITOR;
					}
					break;
				case sf::Event::GainedFocus:
					isFocus = true;
					break;
				case sf::Event::LostFocus:
					isFocus = false;
					break;
				case sf::Event::Resized:
					CommResMeth::resetWindowView(*wnd);
					butStart.resetViewport();
					butEdit.resetViewport();
					butOnline.resetViewport();
					butExit.resetViewport();
					break;
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
					return GAMESTATE_GAME_OFFLINE;
				}
				if (butOnline.getStatus() == CommResMeth::Button::ButtonState::Release) {
					return GAMESTATE_LOBBY;
				}
				if (butEdit.getStatus() == CommResMeth::Button::ButtonState::Release) {
					return GAMESTATE_EDITOR;
				}
				if (butExit.getStatus() == CommResMeth::Button::ButtonState::Release) {
					return GAMESTATE_POP;
				}
			}
			wnd->clear(sf::Color(100, 255, 255));
//			butStart.draw(*wnd);
//			butOnline.draw(*wnd);
//			butEdit.draw(*wnd);
//			butExit.draw(*wnd);
			butStart.draw();
			butOnline.draw();
			butEdit.draw();
			butExit.draw();
			wnd->display();
		}
		return GAMESTATE_POP;
	}
}
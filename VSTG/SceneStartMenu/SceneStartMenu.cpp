#include "SceneStartMenu.h"
#include <assert.h>

namespace DllSceneStartMenu {

	SceneStartMenu::SceneStartMenu(Scene* const parent)
		:
		Scene(parent), isFocus(true), isFullscreen(false), isReturn(false), returnState(GAMESTATE_POP),
		gui(*wnd)
		//		butStart(this, { 550,280 }, CommResMeth::Button::MEDIUM, CommResMeth::TextManager::getText(1)),
		//		butOnline(this, { 550,340 }, CommResMeth::Button::MEDIUM, "Start Online"),
		//		butEdit(this, { 550,400 }, CommResMeth::Button::MEDIUM, CommResMeth::TextManager::getText(2)),
		//		butExit(this, { 550,460 }, CommResMeth::Button::MEDIUM, CommResMeth::TextManager::getText(3))
	{
		theme = tgui::Theme::create("widgets/Black.txt");
		button = theme->load("Button");
		button->setSize(150, 50);
		
		button->setPosition(550, 280);
		button->setText(CommResMeth::TextManager::getText(1));
		button->connect("Pressed", &SceneStartMenu::onStartPressed, this);
		gui.add(button);
		button = tgui::Button::copy(button);
		
		button->setPosition(550, 340);
		button->setText(CommResMeth::TextManager::getText(15));
		button->connect("Pressed", &SceneStartMenu::onOnlinePressed, this);
		gui.add(button);
		button = tgui::Button::copy(button);
		
		button->setPosition(550, 400);
		button->setText(CommResMeth::TextManager::getText(2));
		button->connect("Pressed", &SceneStartMenu::onEditPressed, this);
		gui.add(button);
		button = tgui::Button::copy(button);
		
		button->setPosition(550, 460);
		button->setText(CommResMeth::TextManager::getText(3));
		button->connect("Pressed", &SceneStartMenu::onExitPressed, this);
		gui.add(button);
		button = tgui::Button::copy(button);
	}

	SceneStartMenu::~SceneStartMenu() {
		gui.removeAllWidgets();
	}

	int SceneStartMenu::Exec() {

		while (!isReturn && wnd->isOpen()) {
			while (wnd->pollEvent(e)) {
				switch (e.type) {
				case sf::Event::KeyPressed:
					if (e.key.code == sf::Keyboard::Return) {
						if (e.key.system) {
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
					if (e.key.code == sf::Keyboard::E) {
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
//					butStart.resetViewport();
//					butEdit.resetViewport();
//					butOnline.resetViewport();
//					butExit.resetViewport();
					break;
				default:
					CommResMeth::defHandleMsg(*wnd, e);
				}
				gui.handleEvent(e);
			}

//			if (isFocus) {
//				// Button Update
//				butStart.update();
//				butOnline.update();
//				butEdit.update();
//				butExit.update();

//				// Button Handle
//				if (butStart.getStatus() == CommResMeth::Button::ButtonState::Release) {
//					return GAMESTATE_GAME_OFFLINE;
//				}
//				if (butOnline.getStatus() == CommResMeth::Button::ButtonState::Release) {
//					return GAMESTATE_LOBBY;
//				}
//				if (butEdit.getStatus() == CommResMeth::Button::ButtonState::Release) {
//					return GAMESTATE_EDITOR;
//				}
//				if (butExit.getStatus() == CommResMeth::Button::ButtonState::Release) {
//					return GAMESTATE_POP;
//				}
//			}
			wnd->clear(sf::Color(100, 255, 255));
//			butStart.draw(*wnd);
//			butOnline.draw(*wnd);
//			butEdit.draw(*wnd);
//			butExit.draw(*wnd);
//			butStart.draw();
//			butOnline.draw();
//			butEdit.draw();
//			butExit.draw();
			gui.draw();
			wnd->display();
		}

		return returnState;
	}
}
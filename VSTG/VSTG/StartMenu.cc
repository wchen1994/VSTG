#include "StartMenu.hpp"
#include "Essential.hpp"

StartMenu::StartMenu(sf::RenderWindow *wnd){
	this->wnd = wnd;
	font.loadFromFile("res/Symbola_hint.ttf");
	text.setString("Pressed Enter to Continue");
	text.setFont(font);
}

Essential::GameState StartMenu::Run(){
	while(wnd->isOpen()){
		while(wnd->pollEvent(event)){
			switch(event.type){
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Return){
						Essential::isGameOver = false;
						return Essential::GAME;
					}
					break;
				default:
					Essential::defHandleMsg(event);
			}
		}
		wnd->clear(sf::Color(100,255,255));
		wnd->draw(text);
		wnd->display();
	}
	return Essential::POP;
}

#pragma once

#include "GameObject.hpp"
#include "Button.h"

class ObjMenu : public GameObject {
public:
	enum MENUFLAG{OK_CANCEL, YES_NO, OK};
public:
	ObjMenu(sf::IntRect rect, sf::String title, uint32_t flag);
	void Init();
	uint32_t MenuUpdate();
	void Draw(sf::RenderTarget& gfx);
private:
	uint32_t flag;
	sf::Sprite bg;
	std::shared_ptr<sf::Texture> menuTexture;
	std::shared_ptr<sf::Texture> butTexture;
	sf::String title;
	sf::Text text;
	sf::IntRect rect;
	Button but1;	
	Button but2;	
	Button but3;
	bool hasInit;
};
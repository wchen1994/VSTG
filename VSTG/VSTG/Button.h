#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Button {
public:
	enum ButtonState { Idle, Push, Focus, Count };
public:
	Button();
	void setTexture(sf::String tex) {textureName = tex;}
	void setLable(sf::String s) { lable = s; }
	void setSprites(const sf::Vector2i &ipos, const sf::Vector2i &ppos, const sf::Vector2i &fpos, const sf::Vector2i &size);
	void setSprites(const sf::Vector2i pos[], const sf::Vector2i & size);
	void setPosition(const sf::Vector2f & pos);
	void Update();
	void Draw(sf::RenderTarget &gfx);
	void setState(ButtonState s) { state = s; }
	bool test = true;
	ButtonState getStatus() const { return state; }
public:
	enum ButtonStyle{SMALL, MEDIUM, COUNT};
	static void SettingDefaultButton(Button & but, sf::String lable, ButtonStyle style);
private:
	ButtonState state;
	sf::Vector2f position;
	sf::Vector2i size;
	sf::Sprite sprites[3];
	sf::String textureName;
	sf::Text text;
	sf::String lable;
	std::shared_ptr<sf::Texture> pTex;
};
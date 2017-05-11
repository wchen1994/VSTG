#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
	enum ButtonState { Idle, Push, Focus, Count };
public:
	Button() { state = ButtonState::Idle; }
	Button(sf::Texture texture,sf::String);
	void setTexture(sf::Texture tex) { texture = tex; }
	void setLable(sf::String s) { lable = s; }
	void setSprites(const sf::Vector2i &ipos, const sf::Vector2i &ppos, const sf::Vector2i &fpos, const sf::Vector2i &size);
	void setSprites(const sf::Vector2i pos[], const sf::Vector2i & size);
	void Update();
	void Draw(sf::RenderTarget &gfx);
	void setState(ButtonState s) { state = s; }
	bool test = true;
	ButtonState getStatus() const { return state; }
private:
	ButtonState state;
	sf::Vector2i position;
	sf::Vector2i size;
	sf::Sprite sprites[3];
	sf::Texture texture;
	sf::Text text;
	sf::String lable;
};
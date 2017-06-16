#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <thread>
#include <cstring>

#include "Essential.hpp"

class TextBox {
public:
	static constexpr int flagALPHABET = 1 << 0;
	static constexpr int flagDIGIT = 1 << 1;
	static constexpr int flagSIMBOL = 1 << 2;
	static constexpr int flagSPACE = 1 << 3;
	static constexpr int flagDEFAULT = flagALPHABET | flagDIGIT | flagSIMBOL | flagSPACE;
	int flag;
public:
	TextBox(sf::Texture & texture, sf::IntRect & rectFocus, sf::IntRect & rectIdle);
	TextBox();

	void Update();
	void Input(const sf::Event::KeyEvent& keyevent);
	void Draw(sf::RenderTarget & gfx);
	void SetPosition(const sf::Vector2f & pos) {
		bgFocus.setPosition(pos); bgIdle.setPosition(pos); text.setPosition(pos);
		rect.left = int(pos.x); rect.top = int(pos.y);
	}
	void UpdateText() {
		if (input.size() == 0) {
			text.setString(prompt);
		}
		else {
			text.setString(input);
		}
	}
private:
	int size;
	sf::IntRect rect;
	sf::Sprite bgIdle;
	sf::Sprite bgFocus;
	sf::Text text;
	bool isFocus;
	std::string input;
	std::string prompt;
	std::shared_ptr<sf::Texture> pTex;
public:
	void SetMaxSize(const int s) { size = s; }
	int GetMaxSize() const { return size; }

	void SetString(const std::string & s) { input = s; UpdateText(); }
	std::string GetString() const { return input; }

	void SetPrompt(const std::string & s) { prompt = s; UpdateText(); }
	std::string GetPrompt() const { return prompt; }


};
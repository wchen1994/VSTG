#include "TextBox.h"

namespace CommResMeth {

	TextBox::TextBox(sf::Texture & texture, sf::IntRect & rectFocus, sf::IntRect & rectIdle, Scene* const parent) :
		Scene(parent), isFocus(false), flag(flagDEFAULT), size(12)
	{
		bgIdle.setTexture(texture);
		bgIdle.setTextureRect(rectIdle);

		bgFocus.setTexture(texture);
		bgFocus.setTextureRect(rectFocus);

		rect = sf::FloatRect(0, 0, float(rectFocus.left), float(rectFocus.width));
	}

	TextBox::TextBox(Scene* const parent) :
		Scene(parent), isFocus(false), flag(flagDEFAULT), size(12)
	{
		pTex = AssetManager::GetTexture("Resources/Textures/TextBox01.png");
		bgFocus.setTexture(*pTex);
		bgFocus.setTextureRect(sf::IntRect(0, 0, 300, 40));
		bgIdle.setTexture(*pTex);
		bgIdle.setTextureRect(sf::IntRect(0, 90, 300, 40));
		rect = sf::FloatRect(0, 0, 300, 40);

		pFont = AssetManager::GetFont("Resurces/Fonts/msyh.ttf");
		text.setString(prompt);
		text.setFont(*pFont);
	}

	void TextBox::Update()
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			const sf::Vector2i & pos = sf::Mouse::getPosition(*wnd);
			sf::Vector2f fpos = { float(pos.x), float(pos.y) };
			fpos /= windowScale;
			if (inRect(rect, fpos)) {
				isFocus = true;
			}
			else {
				isFocus = false;
			}
		}
	}

	void TextBox::Input(const sf::Event::KeyEvent & keyevent)
	{
		sf::Keyboard::Key key = keyevent.code;
		if (!isFocus)
			return;
		if (int(input.size()) < size) {
			if (flag & flagALPHABET) {
				if (keyevent.shift) {
					if (key >= sf::Keyboard::Key::A && key <= sf::Keyboard::Key::Z) {
						input.push_back('A' + key - sf::Keyboard::Key::A);
					}
				}
				else {
					if (key >= sf::Keyboard::Key::A && key <= sf::Keyboard::Key::Z) {
						input.push_back('a' + key - sf::Keyboard::Key::A);
					}
				}
			}
			if (flag & flagDIGIT) {
				if (key >= sf::Keyboard::Key::Num0 && key <= sf::Keyboard::Key::Num9) {

					input.push_back('0' + key - sf::Keyboard::Key::Num0);
				}
			}
			if (flag & flagSIMBOL) {
				if (key == sf::Keyboard::Key::Period) {
					input.push_back('.');
				}
			}
		}
		if (key == sf::Keyboard::Key::BackSpace) {
			if (input.size() != 0)
				input.pop_back();
		}
		UpdateText();
	}

	void TextBox::Draw(sf::RenderTarget & gfx)
	{
		if (isFocus) {
			gfx.draw(bgFocus);
			gfx.draw(text);
		}
		else {
			gfx.draw(bgIdle);
			gfx.draw(text);
		}
	}
}
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Defines.h"
#include "Scene.hpp"

namespace CommResMeth {
	class __VSTG_API Button : public Scene {
	public:
		enum ButtonState { Idle, Push, Focus, Release, Count };
	public:
		explicit Button(Scene* const parent = nullptr);
		void setTexture(const sf::String & tex);
		void setLable(const sf::String & s);
		void setSprites(const sf::Vector2i &ipos, const sf::Vector2i &ppos, const sf::Vector2i &fpos, const sf::Vector2i &size);
		void setPosition(const sf::Vector2f & pos);
		void Update() override;
		void draw(sf::RenderTarget &gfx);
		void setState(ButtonState s) { state = s; }
		ButtonState getStatus() const { return state; }
	public:
		enum ButtonStyle { SMALL, MEDIUM, COUNT };
		static Button createDefaultButton(const sf::String & lable, ButtonStyle style, Scene* const parent = nullptr);
	private:
		ButtonState state;
		sf::Vector2f position;
		sf::Vector2i size;
		sf::Sprite sprites[3];
		sf::Text text;
		std::shared_ptr<sf::Texture> pTex;
		std::shared_ptr<sf::Font> pFont;
	};
}
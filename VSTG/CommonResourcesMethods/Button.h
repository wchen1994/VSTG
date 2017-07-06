#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Defines.h"
#include "Scene.h"
#include "AssetManager.h"
#include "Methods.h"

namespace CommResMeth {
	class __VSTG_API Button : public Scene {
	public:
		enum ButtonState { Idle, Push, Focus, Release, Count };
	public:
		explicit Button(Scene* const parent);
		void setTexture(const sf::String & tex);
		void setLable(const sf::String & s);
		void setSprites(const sf::Vector2i &ipos, const sf::Vector2i &ppos, const sf::Vector2i &fpos, const sf::Vector2i &size);
		void setPosition(int x, int y) override;
		void Update() override;
		void draw(sf::RenderTarget &gfx);
		void setState(ButtonState s) { state = s; }
		ButtonState getStatus() const { return state; }
	public:
		enum ButtonStyle { SMALL, MEDIUM, COUNT };
		static Button* processDefaultButton(Button* const but, const sf::String & lable, ButtonStyle style);
	private:
		ButtonState state;
		sf::Sprite sprites[3];
		sf::Text text;
		std::shared_ptr<sf::Texture> pTex;
		std::shared_ptr<sf::Font> pFont;
	};
}
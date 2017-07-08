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
		enum ButtonStyle { SMALL, MEDIUM, COUNT };
	public:
		explicit Button(Scene* const parent, const sf::Vector2i & pos = sf::Vector2i(),
			ButtonStyle style=ButtonStyle::SMALL, const sf::String & label="unamed");
		void setTexture(const sf::String & tex);
		void setLable(const sf::String & s);
		void setSprites(const sf::Vector2i &ipos, const sf::Vector2i &ppos, const sf::Vector2i &fpos, const sf::Vector2i &size);
		void setState(ButtonState s) { state = s; }
		ButtonState getStatus() const { return state; }
	private:
		void Update() override;
		void Draw() override;
	public:
		void setStyle(ButtonStyle style, const sf::String & lable);
	private:
		ButtonState state;
		sf::Sprite sprites[3];
		sf::Text text;
		std::shared_ptr<sf::Texture> pTex;
		std::shared_ptr<sf::Font> pFont;
	};
}
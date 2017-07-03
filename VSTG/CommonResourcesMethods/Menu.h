#pragma once

#include "Defines.h"
#include "Button.h"

#include "Scene.hpp"

namespace CommResMeth {

	class __VSTG_API Menu : public Scene {
	public:
		enum MENUFLAG { OK_CANCEL, YES_NO, OK };
	public:
		Menu(sf::IntRect rect, sf::String title, uint32_t flag, Scene* const parent = nullptr);
		uint32_t MenuUpdate();
		void Draw(sf::RenderTarget& gfx);
		void SetTitle(sf::String title) { this->title = title; text.setString(title); }
	private:
		uint32_t flag;

		sf::Sprite bg;
		sf::Sprite horiBar;
		sf::Sprite vertBar;
		sf::Sprite corner;

		sf::String title;
		sf::Text text;
		sf::IntRect rect;
		Button but1;
		Button but2;
		Button but3;
		static constexpr int padding = 10;
		std::shared_ptr<sf::Texture> pBG;
	};

}
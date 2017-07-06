#pragma once

#include "Defines.h"
#include <SFML/Graphics.hpp>

namespace CommResMeth {

	class __VSTG_API Scene : public sf::IntRect{
	public:
		Scene(Scene* const parent, sf::IntRect rect = sf::IntRect());
		Scene(sf::RenderWindow* const wnd);
		~Scene();
		int exec();
		void update(const float dt);
		void update();
		void move(int x, int y);
		void move(sf::Vector2i & dpos) { move(dpos.x, dpos.y); }
		virtual void setPosition(int x, int y);
		void setPosition(const sf::Vector2i & pos) { setPosition(pos.x, pos.y); }
		virtual void setSize(int w, int h);
		void setSize(const sf::Vector2i & size) { setSize(size.x, size.y); }
	private:
		virtual int Exec();
		virtual void Update(const float dt);
		virtual void Update();
	protected:
		sf::RenderWindow* wnd;
		Scene *parent;
		std::vector<Scene*> childs;
	private:
		bool isCreator;
	};
}
#pragma once

#include "Essential.hpp"

namespace CommResMeth {

	class __declspec(dllexport) Scene {
	public:
		Scene(Scene* const parent = nullptr);
		Scene(sf::RenderWindow* const wnd);
		~Scene();
		GameState exec();
		void update(const float dt);
		void update();
	private:
		virtual GameState Exec();
		virtual void Update(const float dt);
		virtual void Update();
	protected:
		sf::RenderWindow* wnd;
		sf::Vector2u wndSize;
	private:
		bool isCreator;
	};
}
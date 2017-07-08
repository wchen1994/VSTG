#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <iostream>

#include "GameObject.h"
#include "Scene.h"
#include "Board.h"
#include "Renderer.h"
#include "FrameTimer.h"

#pragma comment(lib, "CommonResourcesMethods")

namespace DllSceneBulletHell {

	class __VSTG_API SceneGame : public CommResMeth::Scene {
	public:
		SceneGame(CommResMeth::Scene* const parent);
		~SceneGame();
	private:
		void Update(const float dt) override;
		void Draw() override;
	private:
		Board brd;
		std::shared_ptr<sf::Texture> pBGTex;
		sf::Sprite spriteBG;
	};

	class __VSTG_API SceneBulletHell : public CommResMeth::Scene {
	public:
		SceneBulletHell(CommResMeth::Scene* const parent);
		int Exec() override;
	};
}


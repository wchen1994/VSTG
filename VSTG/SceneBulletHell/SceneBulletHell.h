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
	class Player : public virtual GameObject, public virtual Renderer/*, public virtual BoardObj*/ {
	public:
		static std::shared_ptr<Player> Create(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex) {
			std::shared_ptr<Player> pPlayer = std::make_shared<Player>(pos, pTex);
			layerDefault[pPlayer->unique_id] = pPlayer;
			return pPlayer;
		}
		Player(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex) :
			Moveable(pos),
			GameObject(nullptr, pos, 0.f, "player"),
			Renderer(pTex, sf::Vector2f(pTex->getSize().x/2.f, pTex->getSize().y/2.f), sf::Vector2f(0.1f, 0.1f))
		{
		}
	};

	class SceneGame : public CommResMeth::Scene {
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
		std::shared_ptr<GameObject> player;
		std::shared_ptr<GameObject> player2;
	};

	class __VSTG_API SceneBulletHell : public CommResMeth::Scene {
	public:
		SceneBulletHell(CommResMeth::Scene* const parent);
		int Exec() override;
	};
}


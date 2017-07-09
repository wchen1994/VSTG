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
	class Player : public virtual GameObject, public virtual Renderer, public virtual BoardObj {
	public:
		static std::shared_ptr<Player> Create(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, Board *brd) {
			std::shared_ptr<Player> pPlayer = std::make_shared<Player>(pos, pTex, brd);
			layerDefault[pPlayer->unique_id] = pPlayer;
			return pPlayer;
		}
		Player(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, Board *brd) :
			Moveable(pos),
			GameObject(nullptr, pos, 0.f, "player"),
			Renderer(pTex, sf::Vector2f(pTex->getSize().x/2.f, pTex->getSize().y/2.f), sf::Vector2f(0.1f, 0.1f)),
			BoardObj(brd, ColliderType::Circle, ColliderProperities(5.f)),
			Collider(ColliderType::Circle, ColliderProperities(5.f))
		{
		}
	};

	class HappyTree : public virtual GameObject, public virtual Renderer, public virtual BoardObj {
	public:
		static std::shared_ptr<HappyTree> Create(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, std::shared_ptr<sf::Texture> pTex2, Board *brd) {
			std::shared_ptr<HappyTree> pObj = std::make_shared<HappyTree>(pos, pTex, pTex2, brd);
			layerDefault[pObj->unique_id] = pObj;
			return pObj;
		}
		HappyTree(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, std::shared_ptr<sf::Texture> pTex2, Board *brd) :
			Moveable(pos),
			GameObject(nullptr, pos, 0.f, "player"),
			Renderer(pTex, sf::Vector2f(pTex->getSize().x / 2.f, pTex->getSize().y / 2.f), sf::Vector2f(0.1f, 0.1f)),
			BoardObj(brd, ColliderType::Circle, ColliderProperities(5.f)),
			Collider(ColliderType::Circle, ColliderProperities(5.f)),
			pTex2(pTex2), isRed(false)
		{
		}

		void OnCollisionEnter(Collider* const other) override {
			GameObject *pM = dynamic_cast<GameObject*>(other);
			if (isRed)
				sprite.setTexture(*pTex2);
			else
				sprite.setTexture(*pTex);
			isRed = !isRed;
		}
	private:
		std::shared_ptr<sf::Texture> pTex2;
		bool isRed;
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
		std::shared_ptr<HappyTree> objTree;
	};

	class __VSTG_API SceneBulletHell : public CommResMeth::Scene {
	public:
		SceneBulletHell(CommResMeth::Scene* const parent);
		int Exec() override;
	};
}


#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "Board.h"
#include "BehaviourController.h"

static BinTree *CreatePlayerTree();

namespace ObjCreator {

	class Character : public virtual GameObject, public virtual Renderer, public virtual BoardObj, public virtual BehaviourController {
	public:
		static std::shared_ptr<Character> Create(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, Board *brd);

		Character(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, Board *brd);

	public:
		void setVelocity(const sf::Vector2f & vel);
		float getSpeed() const { return speed; }

	protected:
		void Update(const float dt) override {
			updateBehaviour(dt);
		}

		void FixedUpdate(const float dt) override {
			position += velocity * speed * dt;
		}

	protected:
		sf::Vector2f velocity;
		float speed;
	};

	class Player : public Character {
	public:
		static std::shared_ptr<Player> Create(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, Board *brd);

		Player(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, Board *brd);

		void onFire(const float dt);

	private:
		float hp;
		static constexpr float coolDown = 0.3f;
		float counter;
	};
}
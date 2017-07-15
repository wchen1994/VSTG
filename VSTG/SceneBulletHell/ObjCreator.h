#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "Board.h"
#include "BehaviourController.h"

static BinTree *CreatePlayerTree();

namespace ObjCreator {

	class Character : public virtual GameObject, public virtual Renderer, public virtual BoardObj, public virtual BehaviourController {
	public:
		static std::shared_ptr<Character> Create(const sf::Vector2f & pos, const sf::Vector2f & vel, float speed, std::shared_ptr<sf::Texture> pTex, Board *brd);

		Character(const sf::Vector2f & pos, const sf::Vector2f & vel, float speed, std::shared_ptr<sf::Texture> pTex, Board *brd);

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
		static std::shared_ptr<Player> Create(const sf::Vector2f & pos, std::shared_ptr<sf::Texture> pTex, Board *brd);

		Player(const sf::Vector2f & pos, std::shared_ptr<sf::Texture> pTex, Board *brd);

		void PostUpdate() override;

		void onFire(const float dt);

	private:
		float hp;
		static constexpr float coolDown = 0.01f;
		float counter;
	};

	class PlayerBullet : public Character {
	public:
		static std::shared_ptr<PlayerBullet> Create(
			const sf::Vector2f & pos, const CommResMeth::Angle & angle, float speed, std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & scale, Board *brd);

		PlayerBullet(
			const sf::Vector2f & pos, const CommResMeth::Angle & angle, float speed, std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & scale, Board *brd);

		void PostUpdate() override;
	};
}
#include <cstdlib>

#include "Essential.hpp"
#include "Game.hpp"
#include "Board.hpp" 
#include "Player.hpp" 
#include "Enemy.hpp"


std::set<std::shared_ptr<GameObject>> Game::layerDefault;
std::set<std::shared_ptr<GameObject>> Game::layerEnemy;
std::set<std::shared_ptr<GameObject>> Game::layerBullet;
std::set<std::shared_ptr<GameObject>> Game::layerPlayer;
std::set<std::shared_ptr<GameObject>> Game::layerDelete;

Game::Game(sf::RenderWindow& wnd) :
	Scene(),
	wnd(wnd)
{
}

Game::~Game(){
//	for (auto it=layerDefault.begin(); it!=layerDefault.end(); it++){
//		delete *it;
//	}
	layerDefault.clear();
	
//	for (auto it=layerDelete.begin(); it!=layerDelete.end(); it++){
//		delete *it;
//	}
	layerDelete.clear();
}

Essential::GameState Game::Run(){ 
	const std::shared_ptr<Player> pPlayer = std::make_shared<Player>(Player());
	layerDefault.insert(pPlayer);
	layerPlayer.insert(pPlayer);

	while(wnd.isOpen()){ 
		Update();
		if (Essential::isGameOver){
			return Essential::POP;
		}
	}
	return Essential::POP;
}

void Game::Update() {
	//Event Handle
	while (wnd.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			for (auto it = layerDefault.begin();
				it != layerDefault.end(); it++) {
				(*it)->OnKeyPressed(event.key);
			}
			break;
		case sf::Event::KeyReleased:
			for (auto it = layerDefault.begin();
				it != layerDefault.end(); it++) {
				(*it)->OnKeyReleased(event.key);
			}
			break;
		default:
			Essential::defHandleMsg(event);
		}
	}

	//Update
	dt = ft.Mark();
	for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
		(*it)->Update(dt);
	}

	std::cout << "\rFPS: " << 1 / dt;

	//FixedUpdate
	culDt += dt;
	while (culDt >= fixedUpdateDuration) {
		for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
			(*it)->FixedUpdate(fixedUpdateDuration);
		}
		culDt -= fixedUpdateDuration;

		//Enemy create
		const std::shared_ptr<Enemy>pEnemy = std::make_shared<Enemy>(Enemy(float(rand() % 800), 0.0f, 0.0f, 1.0f));
		layerDefault.insert(pEnemy);
		layerEnemy.insert(pEnemy);

		//Collision
		for (auto it = layerEnemy.begin(); it != layerEnemy.end(); it++) {
			for (auto it2 = layerBullet.begin(); it2 != layerBullet.end(); it2++) {
				sf::Vector2<float> diffPos = (*it)->getPosition() - (*it2)->getPosition();
				float len = (*it)->getSize() + (*it2)->getSize();
				if (diffPos.x*diffPos.x + diffPos.y*diffPos.y <= len*len)
					(*it)->OnCollisionEnter(*it2);
			}
			for (auto it2 = layerPlayer.begin(); it2 != layerPlayer.end(); it2++) {
				sf::Vector2<float> diffPos = (*it)->getPosition() - (*it2)->getPosition();
				float len = (*it)->getSize() + (*it2)->getSize();
				if (diffPos.x*diffPos.x + diffPos.y*diffPos.y <= len*len)
					(*it)->OnCollisionEnter(*it2);
			}
		}
	}

	//Remove
	for (auto it = layerDelete.begin(); it != layerDelete.end(); it++) {
		layerDefault.erase(*it);
		layerPlayer.erase(*it);
		layerBullet.erase(*it);
		layerEnemy.erase(*it);
	}
	layerDelete.clear();

	wnd.clear();
	//Drawing
	for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
		(*it)->Draw(wnd);
	}
	wnd.display();
}

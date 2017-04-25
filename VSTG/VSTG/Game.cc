#include <cstdlib>

#include "Essential.hpp"
#include "Game.hpp"
#include "Board.hpp" 
#include "Player.hpp" 
#include "Enemy.hpp"


std::set<std::shared_ptr<GameObject>> Game::layerDefault;
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
	layerDefault.insert(std::make_shared<Player>(Player()));

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

	//Enemy create
	layerDefault.insert(std::make_shared<Enemy>(Enemy( float(rand() % 800), 0.0f, float(rand()%100-59), float(rand()%50) )));

	wnd.clear();

	//Update
	dt = ft.Mark();
	for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
		(*it)->Update(dt);
	}

	//FixedUpdate
	culDt += dt;
	while (culDt >= fixedUpdateDuration) {
		for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
			(*it)->FixedUpdate(fixedUpdateDuration);
		}
		culDt -= fixedUpdateDuration;
	}

	//Collision
	for (auto it=layerDefault.begin(); it != layerDefault.end(); it++){
		for (auto it2=layerDefault.begin(); it2 != layerDefault.end(); it2++){
			if(it != it2){
				sf::Vector2<float> diffPos = (*it)->getPosition() - (*it2)->getPosition();
				float len = (*it)->getSize() + (*it2)->getSize();
				if (diffPos.x*diffPos.x + diffPos.y*diffPos.y <= len*len)
					(*it)->OnCollisionEnter(*it2);
			}
		}
	}

	//Drawing
	for (auto it=layerDefault.begin(); it != layerDefault.end(); it++){
		(*it)->Draw(wnd);
	}

	//Remove
	for (auto it = layerDelete.begin(); it != layerDelete.end(); it++) {
		layerDefault.erase(*it);
	}
	layerDelete.clear();

	wnd.display();
}

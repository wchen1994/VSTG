#include <cstdlib>

#include "Essential.hpp"
#include "Game.hpp"
#include "Board.hpp" 
#include "Player.hpp" 
#include "Enemy.hpp"

Game::Game(sf::RenderWindow *wnd) :
	Scene()
{
	this->wnd = wnd;
	wnd->setFramerateLimit(60);
}

Game::~Game(){
	for (std::set<GameObject*>::iterator it=GameObject::layerDefault.begin(); it!=GameObject::layerDefault.end(); it++){
		delete *it;
	}
	GameObject::layerDefault.clear();
	
	for (std::set<GameObject*>::iterator it=GameObject::layerDelete.begin(); it!=GameObject::layerDelete.end(); it++){
		delete *it;
	}
	GameObject::layerDelete.clear();
}

Essential::GameState Game::Run(){ 
	GameObject::layerDefault.insert(new Player(wnd));

	while(wnd->isOpen()){ 
		Update();
		if (Essential::isGameOver){
			return Essential::POP;
		}
	}
	return Essential::POP;
}

void Game::Update(){
	//Event Handle
	while(wnd->pollEvent(event)){
		switch (event.type){
			case sf::Event::KeyPressed:
				for (std::set<GameObject*>::iterator it=GameObject::layerDefault.begin();
				it != GameObject::layerDefault.end(); it++){
					(*it)->OnKeyPressed(event.key);
				}
				break;
			case sf::Event::KeyReleased:
				for (std::set<GameObject*>::iterator it=GameObject::layerDefault.begin();
				it != GameObject::layerDefault.end(); it++){
					(*it)->OnKeyReleased(event.key);
				}
				break;
			default:
				Essential::defHandleMsg(event);
		}
	}

	//Enemy create
//	GameObject::layerDefault.insert(new Enemy(wnd, rand()%800, 0,
//											rand()%100-50, rand()%50));

	wnd->clear();

	//Update
	for (std::set<GameObject*>::iterator it=GameObject::layerDefault.begin();
		it != GameObject::layerDefault.end(); it++){
		(*it)->Update();
	}

	//Collision
	for (std::set<GameObject*>::iterator it=GameObject::layerDefault.begin();
		it != GameObject::layerDefault.end(); it++){
		for (std::set<GameObject*>::iterator it2=GameObject::layerDefault.begin();
			it2 != GameObject::layerDefault.end(); it2++){
			if(it != it2){
				sf::Vector2<float> diffPos = (*it)->getPosition() - (*it2)->getPosition();
				float len = (*it)->getSize() + (*it2)->getSize();
				if (diffPos.x*diffPos.x + diffPos.y*diffPos.y <= len*len)
					(*it)->OnCollisionEnter(*it2);
			}
		}
	}

	//Drawing
	for (std::set<GameObject*>::iterator it=GameObject::layerDefault.begin();
		it != GameObject::GameObject::layerDefault.end(); it++){
		(*it)->Draw();
	}

	//Remove
	GameObject *pDelete;
	while(!GameObject::layerDelete.empty()){
		pDelete = (*GameObject::layerDelete.begin());
		GameObject::layerDefault.erase(pDelete);
		delete pDelete;
		GameObject::layerDelete.erase(pDelete);
	}

	wnd->display();
}

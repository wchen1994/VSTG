#include"GameObject.hpp"

std::set<GameObject*> GameObject::layerDefault;
std::set<GameObject*> GameObject::layerDelete;

GameObject::GameObject(sf::RenderWindow *wnd) :
	position(0,0)
{
	this->wnd = wnd;
	colliderSize = 0;
	drawing = NULL;
}

GameObject::~GameObject(){
};

void GameObject::Draw(){
	if (drawing){
		wnd->draw(*drawing);
	}
}

void GameObject::Update(){
}

void GameObject::OnKeyPressed(sf::Event::KeyEvent key){
}

void GameObject::OnKeyReleased(sf::Event::KeyEvent key){
}

void GameObject::OnCollisionEnter(GameObject *other){
}


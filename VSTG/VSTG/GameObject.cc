#include"GameObject.hpp"

GameObject::GameObject() :
	position(0,0)
{
	colliderSize = 0;
	drawing = NULL;
}

GameObject::~GameObject(){
};

void GameObject::Draw(sf::RenderWindow& wnd){
	if (drawing){
		wnd.draw(*drawing);
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


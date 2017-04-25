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

void GameObject::Update(const float& dt){
}

void GameObject::FixedUpdate(const float & dt)
{
}

void GameObject::OnKeyPressed(sf::Event::KeyEvent key){
}

void GameObject::OnKeyReleased(sf::Event::KeyEvent key){
}

void GameObject::OnCollisionEnter(std::shared_ptr<GameObject> other){
}


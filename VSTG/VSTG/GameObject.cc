#include"GameObject.hpp"

char GameObject::objectID[128];
size_t GameObject::hashID;

GameObject::GameObject() :
	position(0,0),
	brdPos(0,0),
	enable_shared_from_this()
{
	colliderSize = 0;
	drawing = NULL;
	// Setup ID
	for (auto& c : objectID) {
		c = '\0';
	}
	hashID = 0;
}

GameObject::~GameObject(){
};

void GameObject::Draw(sf::RenderTarget& gfx){
	if (drawing){
		gfx.draw(*drawing);
	}
}

void GameObject::Update(const float dt){
}

void GameObject::FixedUpdate(const float dt)
{
}

void GameObject::OnCollisionEnter(std::shared_ptr<GameObject> pOther){
}


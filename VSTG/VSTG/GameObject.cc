#include"GameObject.hpp"

char GameObject::objectID[128];
size_t GameObject::hashID;

GameObject::GameObject() :
	position(0,0),
	brdPos(0,0),
	drawCollider(nullptr),
	drawSprite(nullptr),
	enable_shared_from_this()
{
	colliderSize = 0;
	// Setup ID
	for (auto& c : objectID) {
		c = '\0';
	}
	hashID = 0;
}

GameObject::~GameObject(){
};

void GameObject::Draw(sf::RenderTarget& gfx){
	if (drawSprite) {
		gfx.draw(*drawSprite);
	}
	else if (drawCollider){
		gfx.draw(*drawCollider);
	} 
#ifdef _DEBUG_COLLIDER
	if (drawCollider) {
		gfx.draw(*drawCollider);
	}
#endif
}

void GameObject::Update(const float dt){
}

void GameObject::FixedUpdate(const float dt)
{
}

void GameObject::OnCollisionEnter(std::shared_ptr<GameObject> pOther){
}


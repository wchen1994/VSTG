#include"GameObject.hpp"

char GameObject::classID[128];
size_t GameObject::hashCID;

GameObject::GameObject() :
	position(0,0),
	brdPos(0,0),
	drawCollider(nullptr),
	drawSprite(nullptr),
	enable_shared_from_this()
{
	colliderSize = 0;
	// Setup ID
	for (int i = 0; i < 128; i++) {
		classID[i] = '\0';
		objectID[i] = '\0';
	}
	hashCID = 0;
	hashOID = 0;
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

GameObject * GameObject::CLone() const
{
	return nullptr;
}




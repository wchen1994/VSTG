#include"GameObject.hpp"

//Static
unsigned int GameObject::uniqueIdCounter = 0;
//Static end

GameObject::GameObject() :
	GameObject(sf::Vector2f(0.0f, 0.0f))
{
}

GameObject::GameObject(sf::Vector2f pos) :
	position(pos),
	isDelete(false),
	type(UNKONW),
	unique_id(++uniqueIdCounter),
	enable_shared_from_this()
{
	// Setup ID
	for (int i = 0; i < 128; i++) {
		objectID[i] = '\0';
	}
	hashOID = 0;


	assert(uniqueIdCounter < UINT32_MAX);
}


GameObject::~GameObject(){
};

void GameObject::Draw(sf::RenderTarget& gfx){
}

void GameObject::Update(const float dt){
}

void GameObject::FixedUpdate(const float dt)
{
}

void GameObject::LateUpdate()
{
}

GameObject * GameObject::CLone() const
{
	return nullptr;
}




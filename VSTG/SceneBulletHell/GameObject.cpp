#include"GameObject.h"

//Static
OBJID GameObject::uniqueIdCounter = 0;
float GameObject::timeCounter = 0.f;
std::queue<std::shared_ptr<GameObject>> GameObject::layerDelete;
std::map<OBJID, std::shared_ptr<GameObject>, GameObject::ObjIdBefore> GameObject::layerDefault;
//Static end

std::shared_ptr<GameObject> GameObject::Create(GameObject * const parent, const sf::Vector2f & pos, const CommResMeth::Angle & rot, char objName[])
{
	std::shared_ptr<GameObject> pObj = std::make_shared<GameObject>(parent, pos, rot, objName);
	layerDefault[pObj->unique_id] = pObj;
	return pObj;
}

GameObject::GameObject(GameObject* const parent, const sf::Vector2f & pos, const CommResMeth::Angle & rot, char objName[]) :
	Moveable(pos, rot),
	unique_id(++uniqueIdCounter),
	parent(parent)
{
	if (parent) {
		parent->childs.push_back(this);
	}

	// Setup ID
	strcpy_s(this->objName, objName);

	assert(uniqueIdCounter < OBJID_MAX);
}


GameObject::~GameObject(){
	if (parent) {
		for (auto itPChild = parent->childs.begin(); itPChild != parent->childs.end();) {
			if (*itPChild == this) {
				itPChild = parent->childs.erase(itPChild);
			}
			else {
				itPChild++;
			}
		}
	}

	for (auto pChild : childs) {
		layerDelete.push(pChild->shared_from_this());
	}
};

void GameObject::Draw(sf::RenderTarget& gfx){
}

void GameObject::PreUpdate()
{
}

void GameObject::Update(const float dt){
}

void GameObject::FixedUpdate(const float dt)
{
}

void GameObject::PostUpdate()
{
}

void GameObject::clearObjects()
{
	processDelete();
	layerDefault.clear();
}

void GameObject::processDelete()
{
	while (layerDelete.size() != 0) {
		auto &pObj = layerDelete.front();
		layerDefault.erase(pObj->unique_id);
		layerDelete.pop();
//		int rc = pObj.use_count();	// Duplicate delete of one obj will cause assertion error.
//		assert(rc == 1);			// however multiple collision cause multiple push of the same obj 
	}
}

std::shared_ptr<GameObject> GameObject::findObject(const OBJID unique_id)
{
	return layerDefault[unique_id];
}

void GameObject::delObject(OBJID unique_id)
{
	layerDelete.push(findObject(unique_id));
}

void GameObject::update(const float dt)
{
	for (auto & pPairObj : layerDefault) {
		pPairObj.second->PreUpdate();
	}
	
	for (auto & pPairObj : layerDefault) {
		pPairObj.second->Update(dt);
	}

#ifndef __FORCED_FIXEDUPDATE
	timeCounter += dt;
	if (timeCounter > 1. / FIXEDUPDATE_RATE) {
		for (auto & pPairObj : layerDefault) {
			pPairObj.second->FixedUpdate(timeCounter);
		}

		timeCounter = 0.;
	}
#else
	timeCounter += dt;
	while (timeCounter > 1. / FIXEDUPDATE_RATE) {
		for (auto & pPairObj : layerDefault) {
			pPairObj.second->FixedUpdate(1. / FIXEDUPDATE_RATE);
		}

		timeCounter -= 1. / FIXEDUPDATE_RATE;
	}
#endif
	
	for (auto pPairObj : layerDefault) {
		pPairObj.second->PostUpdate();
	}
}






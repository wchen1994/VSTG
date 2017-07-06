#pragma once

#include "Defines.h"
#include "Moveable.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <queue>
#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <assert.h>

//#define _DEBUG_COLLIDER
#define OBJNAME_SIZE 128

class GameObject : public virtual Moveable, public std::enable_shared_from_this<GameObject>
{

public: // Constructor Destructor
	GameObject(GameObject* const parent, const sf::Vector2f & pos = sf::Vector2f(), const CommResMeth::Angle & rot = 0, char objName[] = "unknow");
	~GameObject();

public: // Public Static func
	static void clearObjects();
	static void processDelete();
	static std::shared_ptr<GameObject> findObject(const OBJID unique_id);
	static void delObject(OBJID unique_id);
	static void update(const float dt);

public: // operator for set order
	struct ObjIdBefore {
		bool operator()(const OBJID lhs, const OBJID rhs) const {
			if (lhs < rhs)
				return true;
			// return false if equal
			return false;
		}
	};

public: // Public Static variable
	static std::map<OBJID, std::shared_ptr<GameObject>, ObjIdBefore> layerDefault;
	static std::queue<std::shared_ptr<GameObject>> layerDelete;

public: // Geter and seter
	sf::Vector2<float> getPosition() const { return position; }
	void setPosition(const sf::Vector2f &vec) { position = vec; }

	std::string getName() const { return objName; }
	void setName(const std::string id) { strcpy_s(objName, id.c_str()); }

	const unsigned int getUniqueId() const { return unique_id; }

	static size_t getSize() { return layerDefault.size(); }

private: // Private Static
	static OBJID uniqueIdCounter;
	static float timeCounter;

private:
	GameObject* parent;
	std::vector<GameObject*> childs;

protected: // protected func
	template <typename Derived>
	std::shared_ptr<Derived> shared_from_derived()
	{
		return std::static_pointer_cast<Derived>(shared_from_this());
	}

protected: // Virtual func
	virtual void Draw(sf::RenderTarget& gfx);
	virtual void PreUpdate();
	virtual void Update(const float dt);
	virtual void FixedUpdate(const float dt);
	virtual void PostUpdate();

protected: // protected variable
	char objName[OBJNAME_SIZE];
	OBJID unique_id;
};

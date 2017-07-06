#include "Scene.h"

namespace CommResMeth {

	Scene::Scene(Scene* const parent, sf::IntRect rect) : sf::IntRect(rect), isCreator(false), parent(parent)
	{
		if (parent) {
			wnd = parent->wnd;
			parent->childs.push_back(this);
		}
		else {
			wnd = new sf::RenderWindow(sf::VideoMode(left + width, top + height), "unnamed");
			isCreator = true;
		}
	}

	Scene::Scene(sf::RenderWindow* const wnd) : isCreator(false), parent(nullptr), wnd(wnd)
	{
		top = 0;
		left = 0;
		width = wnd->getSize().x;
		height = wnd->getSize().y;
	}


	Scene::~Scene() {
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
		for (auto pChild : childs)
			delete pChild;
		if (isCreator) {
			delete wnd;
		}
	}

	int Scene::exec()
	{
		return Exec();
	}

	int Scene::Exec()
	{
		return 0;
	}

	void Scene::update(const float dt)
	{
		Update(dt);
	}

	void Scene::update()
	{
		Update();
	}

	void Scene::move(int x, int y)
	{
		left += x;
		top += y;
		for (auto pChild : childs)
			pChild->move(x, y);
	}

	void Scene::setPosition(int x, int y)
	{
		int dx, dy;
		if (parent) {
			dx = parent->left + x - left;
			dy = parent->top + y - top;
		}
		else {
			dx = x - left;
			dy = y - top;
		}

		move(dx, dy);
	}

	void Scene::setSize(int w, int h)
	{
		width = w; 
		height = h;
	}

	inline const sf::Vector2f Scene::TopLeftCoord2Window(const sf::Vector2f & vec2)
	{
		return sf::Vector2f(left + vec2.x, top + vec2.y);
	}

	inline const sf::Vector2f Scene::BottomLeftCoord2Window(const sf::Vector2f & vec2)
	{
		return sf::Vector2f(left + vec2.x, top + height - vec2.y);
	}

	inline const sf::Vector2f Scene::Window2TopLeftCoord(const sf::Vector2f & vec2)
	{
		return sf::Vector2f(vec2.x - left, vec2.y - top);
	}

	const sf::Vector2f Scene::Window2BottomLeftCoord(const sf::Vector2f & vec2)
	{
		return sf::Vector2f(vec2.x - left, height - vec2.y + top);
	}

	void Scene::Update(const float dt)
	{
	}

	void Scene::Update()
	{
	}
}
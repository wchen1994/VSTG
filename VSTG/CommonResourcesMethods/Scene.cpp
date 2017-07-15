#include "Scene.h"

namespace CommResMeth {

	Scene::Scene(Scene* const parent, const sf::IntRect & rect, const sf::View & view) : 
		sf::IntRect(rect), isCreator(false), parent(parent), sceneView(view)
	{
		if (parent) {
			left += parent->left;
			top += parent->top;
			wnd = parent->wnd;
			parent->childs.push_back(this);
		}
		else {
			wnd = new sf::RenderWindow(sf::VideoMode(left + width, top + height), "unnamed");
			isCreator = true;
		}
		resetViewport();
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
					break;
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

	void Scene::draw()
	{
		wnd->setView(sceneView);
		Draw();
	}

	void Scene::resetViewport()
	{
		const sf::Vector2u size = wnd->getSize();
		const float scale = getWndScale(*wnd);
		const sf::Vector2f unscaledSize = { size.x / scale, size.y / scale };
		const float offsetX = (unscaledSize.x - DEFAULT_WINDOWS_WIDTH) / 2.f;
		const sf::FloatRect viewport(	(left + offsetX) / unscaledSize.x,	top / (float)DEFAULT_WINDOWS_HEIGHT, 
										width / unscaledSize.x,				height / (float)DEFAULT_WINDOWS_HEIGHT  );
		sceneView.setViewport(viewport);
	}

	void Scene::move(int x, int y)
	{
		left += x;
		top += y;
		for (auto pChild : childs)
			pChild->move(x, y);
		resetViewport();
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
		resetViewport();
	}

	void Scene::Update(const float dt)
	{
	}

	void Scene::Update()
	{
	}
}
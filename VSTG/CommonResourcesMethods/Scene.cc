#include "Scene.hpp"

namespace CommResMeth {

	Scene::Scene(Scene* const parent) : isCreator(false)
	{
		if (parent) {
			wnd = parent->wnd;
			wndSize = wnd->getSize();
		}
		else {
			wndSize = { 0,0 };
			wnd = new sf::RenderWindow(sf::VideoMode(wndSize.x, wndSize.y), "unnamed");
			isCreator = true;
		}
	}

	Scene::Scene(sf::RenderWindow * const wnd_in) : isCreator(false)
	{
		if (wnd_in) {
			wnd = wnd_in;
			wndSize = wnd->getSize();
		}
		else {
			wndSize = { 0,0 };
			wnd = new sf::RenderWindow(sf::VideoMode(wndSize.x, wndSize.y), "unnamed");
			isCreator = true;
		}
	}

	Scene::~Scene() {
		if (isCreator)
			delete wnd;
	}

	CommResMeth::GameState Scene::exec()
	{
		return Exec();
	}

	CommResMeth::GameState Scene::Exec()
	{
		return CommResMeth::GameState::POP;
	}

	void Scene::update(const float dt)
	{
		Update(dt);
	}

	void Scene::update()
	{
		Update();
	}

	void Scene::Update(const float dt)
	{
	}

	void Scene::Update()
	{
	}
}
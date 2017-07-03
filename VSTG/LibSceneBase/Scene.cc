#include "Scene.hpp"


Scene::Scene(sf::RenderWindow* const wnd) : wnd(wnd)
{
	if (wnd) {
		wndSize = wnd->getSize();
	}
	else {
		wndSize = { 0,0 };
	}
}

Scene::~Scene(){
}

CommResMeth::GameState Scene::exec()
{
	if (wnd) {
		return Exec();
	}
	else {
		sf::RenderWindow newWnd(sf::VideoMode(wndSize.x, wndSize.y), "unnamed");
	}
}

CommResMeth::GameState Scene::Exec()
{
	return CommResMeth::GameState::POP;
}

void Scene::update(float dt)
{
	if (wnd) {
		Update(dt);
	}
}

void Scene::Update(float dt)
{
}

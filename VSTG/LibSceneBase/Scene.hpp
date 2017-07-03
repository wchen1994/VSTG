#pragma once

#include "Essential.hpp"

class __declspec(dllexport) Scene{
public:
	Scene(sf::RenderWindow* const wnd = nullptr);
	~Scene();
	CommResMeth::GameState exec();
	virtual CommResMeth::GameState Exec();
	void update(float dt);
	virtual void Update(float dt);
protected:
	sf::RenderWindow* const wnd;
	sf::Vector2u wndSize;
};

#pragma once

#include "Scene.hpp"
#include "Essential.hpp"
#include "Button.h"

#pragma comment(lib, "LibSceneBase")
#pragma comment(lib, "CommonResourcesMethods")

class __declspec(dllexport) SceneStartMenu : public Scene{
private:
	sf::Event event;
	sf::RenderWindow& wnd;
	std::shared_ptr<sf::Texture> butTexture;
	CommResMeth::Button butStart;
	CommResMeth::Button butOnline;
	CommResMeth::Button butEdit;
	CommResMeth::Button butExit;
	bool isFocus;
public:
	SceneStartMenu(sf::RenderWindow& wnd);
	virtual ~SceneStartMenu() = default;
	CommResMeth::GameState Run();
};

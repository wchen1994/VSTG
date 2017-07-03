#include <iostream>
#include <SceneStartMenu.hpp>

#pragma comment(lib, "CommonResourcesMethods")
#pragma comment(lib, "SceneStartMenu")

int main() {
	sf::RenderWindow wnd(sf::VideoMode(800, 600), "Game");
	CommResMeth::Scene MainScene(&wnd);
	DllSceneStartMenu::SceneStartMenu startMenu(&MainScene);
	while (wnd.isOpen()) {
		CommResMeth::GameState rc = startMenu.exec();
		std::cout << int(rc) << std::endl;
	}
	system("pause");
	return 0;
}
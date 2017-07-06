#include <iostream>
#include <SceneStartMenu.h>

#pragma comment(lib, "CommonResourcesMethods")
#pragma comment(lib, "SceneStartMenu")

int main() {
	sf::RenderWindow wnd(sf::VideoMode(800, 600), "Game");
	CommResMeth::Scene MainScene(&wnd);
	DllSceneStartMenu::SceneStartMenu startMenu(&MainScene);
	while (wnd.isOpen()) {
		int rc = startMenu.exec();
		std::cout << rc << std::endl;
	}
	system("pause");
	return 0;
}
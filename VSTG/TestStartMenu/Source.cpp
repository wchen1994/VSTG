#include <iostream>
#include <SceneStartMenu.h>

#pragma comment(lib, "CommonResourcesMethods")
#pragma comment(lib, "SceneStartMenu")

int main() {
	sf::RenderWindow wnd(sf::VideoMode(800, 600), "Game");
	CommResMeth::Scene MainScene(&wnd);
	DllSceneStartMenu::SceneStartMenu *pStartMenu;
	while (wnd.isOpen()) {
		pStartMenu = new DllSceneStartMenu::SceneStartMenu(&MainScene);
		int rc = pStartMenu->exec();
		delete pStartMenu;
		std::cout << rc << std::endl;
	}
	system("pause");
	return 0;
}
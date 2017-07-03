#include <SceneStartMenu.hpp>
#include <Essential.hpp>

#pragma comment(lib, "DllSceneStartMenu")
#pragma comment(lib, "CommonResourcesMethods")

int main() {
	sf::RenderWindow wnd(sf::VideoMode(CommResMeth::ScreenWidth, CommResMeth::ScreenHeight), "test");
	DllSceneStartMenu::SceneStartMenu startMenu(&wnd);
	startMenu.Exec();
	wnd.close();
	return 0;
}
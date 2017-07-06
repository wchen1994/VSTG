#include <cstdlib>
#include <iomanip>
#include <thread>

#include "SceneBulletHell.h"

namespace DllSceneBulletHell {

	SceneGame::SceneGame(CommResMeth::Scene * const parent) :
		CommResMeth::Scene(parent, sf::IntRect(50, 50, 500, 550)), brd(this, sf::Vector2i(100, 100))
	{
	}

	SceneGame::~SceneGame() {
		brd.clear();
	}

	void SceneGame::Update(const float dt)
	{
		GameObject::update(dt);
		brd.processCollision();
		GameObject::processDelete();
		wnd->clear();
		Renderer::draw(*wnd);
		wnd->display();
	}

	SceneBulletHell::SceneBulletHell(CommResMeth::Scene * const parent) : Scene(parent, sf::IntRect(0,0,800,600))
	{
	}

	int SceneBulletHell::Exec()
	{
		DllSceneBulletHell::SceneGame *sceneGame = new DllSceneBulletHell::SceneGame(this);
		CommResMeth::FrameTimer ft;
		ft.Mark();
		Canvas mainCanvas(sceneGame, { 0,0,sceneGame->width,sceneGame->height }, { 0,0,100,100 });
		mainCanvas.setBackground(CommResMeth::AssetManager::GetTexture("Resources/Textures/Enemy02.png"));
		while (wnd->isOpen()) {
			sf::Event e;
			while (wnd->pollEvent(e)) {
				CommResMeth::defHandleMsg(*wnd, e);
			}

			sceneGame->update(ft.Mark());
		}
		delete sceneGame;

		return 0;
	}

}
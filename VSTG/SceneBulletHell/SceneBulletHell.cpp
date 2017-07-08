#include <cstdlib>
#include <iomanip>
#include <thread>

#include "SceneBulletHell.h"

namespace DllSceneBulletHell {

	SceneGame::SceneGame(CommResMeth::Scene * const parent) :
		CommResMeth::Scene(parent, sf::IntRect(25, 25, 500, 550)), brd(this, sf::Vector2i(100, 100)), 
		gameView(BottomLeftCoord2TopLeftCoord(sf::Vector2f(width/2.f, height/2.f)), sf::Vector2f((float)width, (float)height))
	{
		pBGTex = CommResMeth::AssetManager::GetTexture("Resources/Textures/Background.png");
		spriteBG.setTexture(*pBGTex);
		sf::Vector2f scale = { (float)width / pBGTex->getSize().x, (float)height / pBGTex->getSize().y };
		spriteBG.setScale(scale);
		spriteBG.setPosition(BottomLeftCoord2TopLeftCoord(sf::Vector2f(0.f, (float)height)));
		resetViewport();
	}

	SceneGame::~SceneGame() {
		brd.clear();
	}

	void SceneGame::Update(const float dt)
	{
		GameObject::update(dt);
		brd.processCollision();
		GameObject::processDelete();
	}

	void SceneGame::Draw()
	{
		wnd->setView(gameView);
		wnd->draw(spriteBG);
		Renderer::draw(*wnd);
	}

	void SceneGame::resetViewport()
	{
		const sf::Vector2u size = wnd->getSize();
		const float scale = CommResMeth::getWndScale(*wnd);
		const sf::Vector2f unscaledSize = { size.x / scale, size.y / scale };
		const float offsetX = (unscaledSize.x - 800) / 2.f;
		gameView.setViewport(sf::FloatRect((25 + offsetX) / unscaledSize.x, 25 / 600.f, 500 / unscaledSize.x, 550 / 600.f));
	}

	SceneBulletHell::SceneBulletHell(CommResMeth::Scene * const parent) : Scene(parent, sf::IntRect(0,0,800,600))
	{
	}

	int SceneBulletHell::Exec()
	{
		DllSceneBulletHell::SceneGame *sceneGame = new DllSceneBulletHell::SceneGame(this);
		CommResMeth::FrameTimer ft;
		ft.Mark();

		while (wnd->isOpen()) {
			sf::Event e;
			while (wnd->pollEvent(e)) {
				switch (e.type) {
				case sf::Event::Resized:
					CommResMeth::resetView(*wnd);
					sceneGame->resetViewport();
					break;
				default:
					CommResMeth::defHandleMsg(*wnd, e);
				}
			}
			sceneGame->update(ft.Mark());

			wnd->clear();
			CommResMeth::resetView(*wnd);
			/*
			Draw Scene widgets if necessary
			*/
			sceneGame->Draw();
			wnd->display();
		}

		delete sceneGame;

		return 0;
	}

}
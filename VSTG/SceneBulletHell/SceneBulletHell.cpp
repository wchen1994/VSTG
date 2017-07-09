#include <cstdlib>
#include <iomanip>
#include <thread>

#include "SceneBulletHell.h"

#define WORLD_HEIGHT (500.f)
#define WORLD_WIDTH (500.f)

namespace DllSceneBulletHell {

	SceneGame::SceneGame(CommResMeth::Scene * const parent) :
		CommResMeth::Scene(parent, sf::IntRect(25, 25, 500, 550), 
			sf::View(BottomLeftCoord2TopLeftCoord(sf::Vector2f(WORLD_WIDTH/2,WORLD_HEIGHT/2)), sf::Vector2f(WORLD_WIDTH, WORLD_HEIGHT))),
		brd(this, sf::IntRect(25, 0, 500, 600), sf::Vector2i(100, 100))
	{
		pBGTex = CommResMeth::AssetManager::GetTexture("Resources/Textures/Background.png");
		spriteBG.setTexture(*pBGTex);
		sf::Vector2f scale = { (float)width / pBGTex->getSize().x, (float)height / pBGTex->getSize().y };
		spriteBG.setScale(scale);
		spriteBG.setPosition(BottomLeftCoord2TopLeftCoord(sf::Vector2f(0.f, (float)height)));

		player = Player::Create(
			sf::Vector2f(300, 250), CommResMeth::AssetManager::GetTexture("Resources/Textures/player00.png"), &brd);
		player = Player::Create(
			sf::Vector2f(200, 250), CommResMeth::AssetManager::GetTexture("Resources/Textures/player00.png"), &brd);

		objTree = HappyTree::Create(
			sf::Vector2f(170, 250), CommResMeth::AssetManager::GetTexture("Resources/Textures/Enemy03.png"), 
			CommResMeth::AssetManager::GetTexture("Resources/Textures/Enemy02.png"), &brd);
		objTree = nullptr;
	}

	SceneGame::~SceneGame() {
		brd.clear();
	}

	void SceneGame::Update(const float dt)
	{
		GameObject::update(dt);
		brd.updateObjsBrdPos();
		brd.processCollision();
		size_t numb = brd.getCountNumb();
		GameObject::processDelete();
	}

	void SceneGame::Draw()
	{
		wnd->draw(spriteBG);
		Renderer::draw(*wnd);
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
					CommResMeth::resetWindowView(*wnd);
					sceneGame->resetViewport();
					break;
				default:
					CommResMeth::defHandleMsg(*wnd, e);
				}
			}
			sceneGame->update(ft.Mark());

			wnd->clear();
			sceneGame->draw();
			wnd->display();
		}

		GameObject::clearObjects();
		delete sceneGame;

		system("pause");

		return 0;
	}

}
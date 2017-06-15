#include <cstdlib>
#include <iomanip>

#include "Essential.hpp"
#include "SceneGame.hpp"
#include "Board.hpp" 
#include "ObjPlayer.hpp" 
#include "ObjEnemy.hpp"
#include "ObjCharacter.h"


std::set<std::shared_ptr<ObjCharacter>> SceneGame::layerDefault;
std::set<std::shared_ptr<ObjCharacter>> SceneGame::layerBullet;
std::set<std::shared_ptr<ObjCharacter>> SceneGame::layerPlayer;
std::set<std::shared_ptr<ObjCharacter>> SceneGame::layerEnemy;
std::set<std::shared_ptr<ObjCharacter>> SceneGame::layerEnemyBullet;
std::set<std::shared_ptr<ObjCharacter>> SceneGame::layerDelete;
Board SceneGame::brd(Essential::ScreenWidth, Essential::ScreenHeight, tileWidth, tileHeight);


SceneGame::SceneGame(sf::RenderWindow& wnd) :
	Scene(),
	wnd(wnd),
	map(),
	isFocused(true), isMenuTriger(false), isGameFail(false), isGameSucceed(false),
	levelFileName("Maps/Lv1.tmap"), levelCount(1),
	escMenu(sf::IntRect(50, 80, 206, 139), Essential::textManager.getText(4), ObjMenu::MENUFLAG::YES_NO)
{
	background.setPosition(Essential::vec2i2f(Essential::GameCanvas.left, Essential::GameCanvas.top));
	background.setSize(Essential::vec2i2f(Essential::GameCanvas.width, Essential::GameCanvas.height));
	background.setFillColor(sf::Color(100, 100, 100));

	playerHP.setFont(Essential::textFont);
	playerHP.setPosition(sf::Vector2f(600.0f, 80.0f));
	playerHP.setString("HP: 100/100");
}


SceneGame::~SceneGame(){
	layerDefault.clear();
	layerBullet.clear();
	layerPlayer.clear();
	layerDelete.clear();
	brd.clear();
}

Essential::GameState SceneGame::Run(){
	if (!Essential::isClient)
		pPlayer = ObjCreator::CreatePlayer(ObjCreator::PlayerType::HULUWA, sf::Vector2f(0.0f, 0.0f));
	
	Reset();

	while (wnd.isOpen()) {
		//Event Handle
		while (wnd.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					isMenuTriger = !isMenuTriger;
				break;
			case sf::Event::LostFocus:
				isFocused = false;
				break;
			case sf::Event::GainedFocus:
				isFocused = true;
				break;
			default:
				Essential::defHandleMsg(event);
			}
		}
		if (isFocused) {
			if (!isMenuTriger) {
				Update();
			}
			else {
				ft.Mark();
				const int rc = escMenu.MenuUpdate();
				switch (rc) {
				case 1:
					isGameFail = true;
					break;
				case 2:
					isMenuTriger = !isMenuTriger;
					break;
				default:
					break;
				}
			}
		}
		else {
			ft.Mark();
		}
		DrawScene();
		if (isGameFail) {
			return Essential::POP;
		}
		if (isGameSucceed) {
			levelCount++;
			levelFileName = "Maps/Lv" + std::to_string(levelCount) + ".tmap";
			Reset();
		}
	}
	return Essential::POP;
}

void SceneGame::Reset()
{
	// Draw Loading Menu
	sf::Text loadingText("Loading ...", Essential::textFont);
	loadingText.setPosition(300.0f, 280.0f);
	Essential::wnd.clear();
	Essential::wnd.draw(loadingText);
	Essential::wnd.display();

	layerDefault.clear();
	layerPlayer.clear();
	layerBullet.clear();
	layerEnemy.clear();
	layerEnemyBullet.clear();
	brd.clear();

	// Create Player
	sf::Vector2f playerPos;
	playerPos.x = float(Essential::GameCanvas.left + Essential::GameCanvas.width / 2);
	playerPos.y = float(Essential::GameCanvas.top + Essential::GameCanvas.height * 4 / 5);
	pPlayer->setPosition(playerPos);
	layerDefault.insert(pPlayer);
	layerPlayer.insert(pPlayer);

	// Load Map
	if (Essential::isClient) {
		if (!map.LoadFromSocket())
			isGameFail = true;
	}
	else {
		if (!map.LoadFile(levelFileName))
			isGameFail = true;
	}

	isGameSucceed = false;
	ft.Mark();
}

void SceneGame::Update() {
	// Check for GameOver
	if (layerPlayer.size() == 0)
		isGameFail = true;

	// Update text
	playerHP.setString("HP: " + std::to_string(int(pPlayer->GetHp())) + "/100");

	//Update
	dt = ft.Mark();
	bool isEnemy = map.Update(dt);
	
	std::vector<size_t>& EnemyCount = brd.GetCount();
	size_t nEnemy = 0;
	for (size_t count : EnemyCount) {
		nEnemy += count;
	}

	if (!isEnemy && nEnemy == 0) {
		isGameSucceed = true;
	}

	for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
		(*it)->Update(dt);
	}

	//FixedUpdate
	culDt += dt;
	while (culDt >= fixedUpdateDuration) {

		for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
			(*it)->FixedUpdate(fixedUpdateDuration);
		}
		culDt -= fixedUpdateDuration;

		for (auto it = layerEnemy.begin(); it != layerEnemy.end(); it++) {
			brd.UpdateObjectPos(*it);
		}
		for (auto it = layerEnemyBullet.begin(); it != layerEnemyBullet.end(); it++) {
			brd.UpdateObjectPos(*it);
		}

		//Bullet collision
		for (auto it = layerBullet.begin(); it != layerBullet.end(); it++) {
			const std::set<std::shared_ptr<Board::Tile>>& sTile = brd.GetPotentialTile(*it);
			for (auto it_tile = sTile.begin(); it_tile != sTile.end(); it_tile++) {
				const std::set<std::shared_ptr<ObjCharacter>>& sObject = (*it_tile)->GetLayer();
				for (auto it2 = sObject.begin(); it2 != sObject.end(); it2++) {
					sf::Vector2<float> diffPos = (*it)->getPosition() - (*it2)->getPosition();
					float len = (*it)->GetColliderSize() + (*it2)->GetColliderSize();
					if (diffPos.x*diffPos.x + diffPos.y*diffPos.y <= len*len)
						(*it)->OnCollisionEnter(*it2);
				}
			}
		}
		// Player collision
		for (auto it = layerPlayer.begin(); it != layerPlayer.end(); it++) {
			std::set<std::shared_ptr<Board::Tile>> sTile = brd.GetPotentialTile(*it);
			for (auto it_tile = sTile.begin(); it_tile != sTile.end(); it_tile++) {
				const std::set<std::shared_ptr<ObjCharacter>> sObject = (*it_tile)->GetLayer();
				for (auto it2 = sObject.begin(); it2 != sObject.end(); it2++) {
					sf::Vector2<float> diffPos = (*it)->getPosition() - (*it2)->getPosition();
					float len = (*it)->GetColliderSize() + (*it2)->GetColliderSize();
					if (diffPos.x*diffPos.x + diffPos.y*diffPos.y <= len*len)
						(*it)->OnCollisionEnter(*it2);
				}
			}
		}
	}

	// LateUpdate
	for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
		(*it)->LateUpdate();
	}

#ifdef _DEBUG_LOG

	//Log
	if (logTimer > 0) {
		logTimer -= dt;
		nDeletes += layerDelete.size();
	}
	else {
		logTimer = 0.5f;
		system("CLS");
		std::cout << "FPS:\t\t" << std::setprecision(1) << std::fixed << 1 / dt << std::endl;
		std::cout << "Objects:\t" << layerDefault.size() << std::endl;
		std::cout << "Bullets:\t" << layerBullet.size() << std::endl;
		std::cout << "Enemys:\t" << layerEnemy.size() << std::endl;
		std::cout << "EnemyBullets:\t" << layerEnemyBullet.size() << std::endl;
		std::cout << "Deletes:\t" << nDeletes << std::endl;
		std::cout << "Brd:Totoal:\t" << nEnemy << std::endl;

		nDeletes = 0;
	}
#endif // _DEBUG

	//Remove
	for (auto it = layerDelete.begin(); it != layerDelete.end(); it++) {
		layerDefault.erase(*it);
		layerPlayer.erase(*it);
		layerBullet.erase(*it);
		layerEnemy.erase(*it);
		layerEnemyBullet.erase(*it);
		brd.RemoveObject(*it);
	}
	layerDelete.clear();
}

void SceneGame::DrawScene()
{
	//Drawing
	wnd.clear();
	
	wnd.draw(background);
	wnd.draw(playerHP);

#ifdef _DEBUG_BOARD
	brd.Highlight(wnd);
	brd.View(wnd);
#endif

	for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
		(*it)->Draw(wnd);
	}
	if (isMenuTriger) {
		escMenu.Draw(wnd);
	}
	wnd.display();
}

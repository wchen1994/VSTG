#include <cstdlib>
#include <iomanip>

#include "Essential.hpp"
#include "Game.hpp"
#include "Board.hpp" 
#include "Player.hpp" 
#include "Enemy.hpp"


std::set<std::shared_ptr<GameObject>> Game::layerDefault;
std::set<std::shared_ptr<GameObject>> Game::layerBullet;
std::set<std::shared_ptr<GameObject>> Game::layerPlayer;
std::set<std::shared_ptr<GameObject>> Game::layerDelete;
Board Game::brd(Essential::ScreenWidth, Essential::ScreenHeight, 50, 50);

Game::Game(sf::RenderWindow& wnd) :
	Scene(),
	wnd(wnd)
{
}

Game::~Game(){
	layerDefault.clear();
	layerBullet.clear();
	layerPlayer.clear();
	layerDelete.clear();
	brd.clear();
}

Essential::GameState Game::Run(){ 
	// Create Player
	const std::shared_ptr<Player> pPlayer = std::make_shared<Player>(Player());
	layerDefault.insert(pPlayer);
	layerPlayer.insert(pPlayer);

	while(wnd.isOpen()){ 
		Update();
		if (Essential::isGameOver){
			return Essential::POP;
		}
	}
	return Essential::POP;
}

void Game::Update() {
	//Event Handle
	while (wnd.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			for (auto it = layerDefault.begin();
				it != layerDefault.end(); it++) {
				(*it)->OnKeyPressed(event.key);
			}
			break;
		case sf::Event::KeyReleased:
			for (auto it = layerDefault.begin();
				it != layerDefault.end(); it++) {
				(*it)->OnKeyReleased(event.key);
			}
			break;
		default:
			Essential::defHandleMsg(event);
		}
	}

	//Update
	dt = ft.Mark();
	for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
		(*it)->Update(dt);
	}

	//FixedUpdate
	culDt += dt;
	while (culDt >= fixedUpdateDuration) {
		// Create Enemy
		const std::shared_ptr<Enemy>pEnemy = std::make_shared<Enemy>(Enemy(float(rand() % 800), 0.0f, 0.0f, 1.0f));
		layerDefault.insert(pEnemy);
		//		layerEnemy.insert(pEnemy);
		brd.AddObject(pEnemy);

		for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
			(*it)->FixedUpdate(fixedUpdateDuration);
		}
		culDt -= fixedUpdateDuration;

		//Bullet collision
		for (auto it = layerBullet.begin(); it != layerBullet.end(); it++) {
			std::set<std::shared_ptr<Board::Tile>> sTile = brd.GetPotentialTile(*it);
			for (auto it_tile = sTile.begin(); it_tile != sTile.end(); it_tile++) {
				const std::set<std::shared_ptr<GameObject>> sObject = (*it_tile)->GetLayer();
				for (auto it2 = sObject.begin(); it2 != sObject.end(); it2++) {
					sf::Vector2<float> diffPos = (*it)->getPosition() - (*it2)->getPosition();
					float len = (*it)->getSize() + (*it2)->getSize();
					if (diffPos.x*diffPos.x + diffPos.y*diffPos.y <= len*len)
						(*it)->OnCollisionEnter(*it2);
				}
			}
		}
		// Player collision
		for (auto it = layerPlayer.begin(); it != layerPlayer.end(); it++) {
			std::set<std::shared_ptr<Board::Tile>> sTile = brd.GetPotentialTile(*it);
			for (auto it_tile = sTile.begin(); it_tile != sTile.end(); it_tile++) {
				const std::set<std::shared_ptr<GameObject>> sObject = (*it_tile)->GetLayer();
				for (auto it2 = sObject.begin(); it2 != sObject.end(); it2++) {
					sf::Vector2<float> diffPos = (*it)->getPosition() - (*it2)->getPosition();
					float len = (*it)->getSize() + (*it2)->getSize();
					if (diffPos.x*diffPos.x + diffPos.y*diffPos.y <= len*len)
						(*it)->OnCollisionEnter(*it2);
				}
			}
		}
	}

	vHLPos.clear();
	for (auto it = layerBullet.begin(); it != layerBullet.end(); it++) {
		const std::vector<sf::Vector2i> sPos = brd.GetPotentialPos(*it);
		for (auto pos : sPos) {
			vHLPos.push_back(pos);
		}
	}

#ifdef _DEBUG

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
		std::cout << "Deletes:\t" << nDeletes << std::endl;
		std::vector<size_t>& EnemyCount = brd.GetCount();
		size_t nEnemy = 0;
		for (size_t count : EnemyCount) {
			nEnemy += count;
		}
		std::cout << "bEnemy:Totoal:\t" << nEnemy << std::endl;

		nDeletes = 0;
	}
#endif // _DEBUG

	//Remove
	for (auto it = layerDelete.begin(); it != layerDelete.end(); it++) {
		layerDefault.erase(*it);
		layerPlayer.erase(*it);
		layerBullet.erase(*it);
		brd.RemoveObject(*it);
	}
	layerDelete.clear();

	wnd.clear();
	//Drawing
#ifdef _BOARD_DEBUG
	for (auto it = vHLPos.begin(); it != vHLPos.end(); it++) {
		brd.HighlightTile(wnd, *it);
	}
	brd.View(wnd);
#endif

	for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
		(*it)->Draw(wnd);
	}
	wnd.display();
}

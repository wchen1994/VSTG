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
std::vector<std::shared_ptr<ObjPlayer>> SceneGame::layerPlayer;
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
	if (Essential::isClient && !Essential::isHost) { // Clinet Start

	}
	else if (!Essential::isClient && Essential::isHost) { // Host Start
		Essential::totalNumbPlayer = int(Essential::socket.GetClinetNumb()) + 1;
		for (int i = 0; i < Essential::totalNumbPlayer; i++) {
			layerPlayer.push_back(ObjCreator::CreatePlayer(ObjCreator::PlayerType::HULUWA, sf::Vector2f(0.0f, 0.0f)));
		}
	}
	else if (!Essential::isClient && !Essential::isHost) { // Offline Start
		layerPlayer.push_back(ObjCreator::CreatePlayer(ObjCreator::PlayerType::HULUWA, sf::Vector2f(0.0f, 0.0f)));
	}
	else
		assert(false);

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
				if(!Essential::isHost && !Essential::isClient)
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
	layerBullet.clear();
	layerEnemy.clear();
	layerEnemyBullet.clear();
	brd.clear();

	// Load Map
	if (Essential::isClient) {
		if (!map.LoadFromSocket())
			isGameFail = true;
	}
	else {
		if (!map.LoadFile(levelFileName))
			isGameFail = true;
	}

	Essential::totalNumbPlayer = int(layerPlayer.size());

	// Change Player Pos
	sf::Vector2f playerPos;
	playerPos.x = float(Essential::GameCanvas.left + Essential::GameCanvas.width / (Essential::totalNumbPlayer + 1));
	playerPos.y = float(Essential::GameCanvas.top + Essential::GameCanvas.height * 4 / 5);
	for (auto &ptrPlayer : layerPlayer) {
		if (ptrPlayer != NULL) {
			ptrPlayer->setPosition(playerPos);
			layerDefault.insert(ptrPlayer);
		}
		playerPos.x += playerPos.x;
	}

	isGameSucceed = false;
	ft.Mark();
}

void SceneGame::Update() {
	// Check for GameOver
	if (!isGameFail) {
		isGameFail = true;
		for (auto &pPlayer : layerPlayer) {
			if (pPlayer != NULL)
				isGameFail = false;
		}
	}

	// Update text
	if (layerPlayer[Essential::playerNumber] != NULL) {
		playerHP.setString("HP: " + std::to_string(int(layerPlayer[Essential::playerNumber]->GetHp())) + "/100");
	}
	else {
		playerHP.setString("HP: 0/100");
	}

	//check whether still enemy have not spon
	dt = ft.Mark();
	bool isEnemy = map.Update(dt);

	//check the current number of enemy
	std::vector<size_t>& EnemyCount = brd.GetCount();
	size_t nBrdObj = 0;
	for (size_t count : EnemyCount) {
		nBrdObj += count;
	}

	// check whether the game is success
	if (!isEnemy && nBrdObj == 0 && !Essential::isClient) {
		isGameSucceed = true;
	}

	//OnlineUpdate : add or delete object
	auto & vPackets = Essential::socket.GetPacket();
	while (!vPackets.empty()) {
		sf::Packet & packet = vPackets.front();
		int type;
		packet >> type;
		switch(Essential::PacketType(type)) {
		case Essential::PacketType::ADD:
			break;
		case Essential::PacketType::REMOVE:
		{
			assert(Essential::isClient);
			uint32_t uni_id;
			packet >> uni_id;
			for (auto & pObject : layerDefault) {
				if (pObject->GetUniId() == uni_id) {
					layerDelete.insert(pObject);
				}
			}
			break;
		}
		case Essential::PacketType::CHANGE:
		{
			int playerNumber;
			ObjPlayer::StructInput Input;
			packet >> playerNumber;
			packet >> Input.isChange >> Input.up >> Input.down >> Input.left >> Input.right >> Input.fire;
			assert(packet.endOfPacket());
			assert(playerNumber >= 0 && playerNumber < Essential::totalNumbPlayer);
			layerPlayer[playerNumber]->UpdateInput(Input);
			break;
		}
		default:
			break;
		}
		vPackets.pop();
	}

	//===========
	// MainUpdate
	//===========
	// Player Input Update
	if (layerPlayer[Essential::playerNumber]) {
		if (Essential::isHost || Essential::isClient) { // Online
			ObjPlayer::StructInput & input = layerPlayer[Essential::playerNumber]->UpdateInput();
			if (input.isChange) {
				sf::Packet packet_out;
				int type = int(Essential::PacketType::CHANGE);
				packet_out << type;
				packet_out << Essential::playerNumber;
				packet_out.append(&input, sizeof(input));
				Essential::socket.SendPacket(packet_out);
			}
		}else if (!Essential::isHost && !Essential::isClient) { // Offline
			layerPlayer[Essential::playerNumber]->UpdateInput();
		}
		else {
			assert(1 != 1);
		}
	}

	// All Obj Update
	if (!Essential::isClient) {
		for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
			(*it)->Update(dt);
		}
	}
	else {
		// Player Update according to input packet
	}

	//FixedUpdate
	culDt += dt;
	while (culDt >= fixedUpdateDuration) {

		for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
			(*it)->FixedUpdate(fixedUpdateDuration);
		}
		culDt -= fixedUpdateDuration;

		// Disable collison n client
		if (!Essential::isClient) {
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

				// layerPlayer is a vector
				if (*it == NULL)
					continue;

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
		std::cout << "Brd:Totoal:\t" << nBrdObj << std::endl;

		nDeletes = 0;
	}
#endif // _DEBUG

	//Remove
	for (auto it = layerDelete.begin(); it != layerDelete.end(); it++) {
		layerDefault.erase(*it);
		layerBullet.erase(*it);
		layerEnemy.erase(*it);
		layerEnemyBullet.erase(*it);
		brd.RemoveObject(*it);
		if ((*it)->GetType() == GameObject::PLAYER) {
			for (auto & pPlayer : layerPlayer) {
				if (pPlayer == *it) {
					pPlayer = NULL;
				}
			}
		}
		
		if (Essential::isHost) {
			assert(!Essential::isClient);
			sf::Packet packet_out;
			uint32_t unique_id = (*it)->GetUniId();
			packet_out << int(Essential::PacketType::REMOVE) << sf::Uint32(unique_id);
			Essential::socket.SendPacket(packet_out);
		}
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

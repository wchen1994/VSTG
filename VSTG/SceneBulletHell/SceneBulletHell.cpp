#include <cstdlib>
#include <iomanip>
#include <thread>

#include "SceneBulletHell.h"


SceneGame::SceneGame(CommResMeth::Scene * const parent) : 
	CommResMeth::Scene(parent, sf::IntRect(50,50, 500,550)), brd(this, sf::Vector2i(100, 100))
{
}

void SceneGame::Update(float dt)
{
	GameObject::update(dt);
	brd.processCollision();
	GameObject::processDelete();
}


std::vector<std::shared_ptr<ObjPlayer>> SceneBulletHell::layerPlayer;
Board SceneBulletHell::brd(CommResMeth::ScreenWidth, CommResMeth::ScreenHeight, tileWidth, tileHeight);


SceneBulletHell::SceneBulletHell(Scene* const parent) :
	Scene(parent),
	map(),
	isFocused(true), isMenuTriger(false), isGameFail(false), isGameSucceed(false),
	levelFileName("Maps/Lv1.tmap"), levelCount(1),
	onlineLatency(0.0f),
	escMenu(sf::IntRect(50, 80, 206, 139), CommResMeth::TextManager::getText(4), CommResMeth::Menu::MENUFLAG::YES_NO)
{
	background.setPosition(CommResMeth::vec2i2f(CommResMeth::CANVAS_LEFT, CommResMeth::CANVAS_TOP));
	background.setSize(CommResMeth::vec2i2f(CommResMeth::CANVAS_WIDTH, CommResMeth::CANVAS_HEIGHT));
	background.setFillColor(sf::Color(100, 100, 100));

	playerHP.setFont(*CommResMeth::AssetManager::GetFont("Resources/Fonts/msyh.ttf"));
	playerHP.setPosition(sf::Vector2f(600.0f, 80.0f));
	playerHP.setString("HP: 100/100");
}


SceneBulletHell::~SceneBulletHell(){
	layerPlayer.clear();
	brd.clear();
}

CommResMeth::GameState SceneBulletHell::Exec(){
	if (socket.isClient() && !socket.isHost) { // Clinet Start

	}
	else if (!socket.isClient() && socket.isHost()) { // Host Start
		totalNumbPlayer = int(socket.GetClinetNumb()) + 1;
		for (int i = 0; i < totalNumbPlayer; i++) {
			layerPlayer.push_back(ObjCreator::CreatePlayer(ObjCreator::PlayerType::HULUWA, sf::Vector2f(0.0f, 0.0f), i));
		}
	}
	else if (!socket.isClient() && !socket.isHost()) { // Offline Start
		layerPlayer.push_back(ObjCreator::CreatePlayer(ObjCreator::PlayerType::HULUWA, sf::Vector2f(0.0f, 0.0f), 0));
	}
	else
		assert(false);

	Reset();

	while (wnd->isOpen()) {
		//Event Handle
		while (wnd->pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					isMenuTriger = !isMenuTriger;
				break;
			case sf::Event::LostFocus:
				if(!socket.isHost() && !socket.isClient())
					isFocused = false;
				break;
			case sf::Event::GainedFocus:
				isFocused = true;
				break;
			default:
				CommResMeth::defHandleMsg(*wnd, event);
			}
		}
		if (isFocused) {
			if (!isMenuTriger) {
				Update();
			}
			else {
				if (socket.isClient() || socket.isHost()) {
					Update(); // Can not stop while playing online
				}
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
			playerNumber = 0;
			totalNumbPlayer = 1;
			socket.setMode(CommResMeth::UDPSocket::Mode::OFFLINE);
			isGameStart = false;
			return CommResMeth::GameState::POP;
		}
		if (isGameSucceed) {
			levelCount++;
			levelFileName = "Maps/Lv" + std::to_string(levelCount) + ".tmap";
			Reset();
		}
	}
	return CommResMeth::GameState::POP;
}

void SceneBulletHell::Reset()
{
	isGameStart = false;
	// Draw Loading Menu
	sf::Text loadingText("Loading ...", *CommResMeth::AssetManager::GetFont("Resources/Fonts/msyh.ttf"));
	loadingText.setPosition(300.0f, 280.0f);
	wnd->clear();
	wnd->draw(loadingText);
	wnd->display();

	GameObject::clearObjects;
	brd.clear();


	// Load Map
	if (socket.isClient()) {
		if (!map.LoadFromSocket())
			isGameFail = true;
	}
	else {
		if (!map.LoadFile(levelFileName))
			isGameFail = true;
	}

	totalNumbPlayer = int(layerPlayer.size());

	// Change Player Pos
	sf::Vector2f playerPos;
	const float xDiff = float(CommResMeth::CANVAS_WIDTH / (totalNumbPlayer + 1));
	playerPos.x = CommResMeth::CANVAS_LEFT + xDiff;
	playerPos.y = float(CommResMeth::CANVAS_TOP + CommResMeth::CANVAS_HEIGHT * 4 / 5);
	for (auto &ptrPlayer : layerPlayer) {
		if (ptrPlayer != NULL) {
			ptrPlayer->setPosition(playerPos);
//			layerDefault.insert(ptrPlayer);  // new instance insert automatically
		}
		playerPos.x += xDiff;
	}

	isGameSucceed = false;
	if (socket.isHost() || socket.isClient())
		socket.Synch();
	std::this_thread::sleep_for(std::chrono::duration<float>(1.0f));
	timeStart = std::chrono::steady_clock::now();
	isGameStart = true;
	synTimer = 0.0f;
	ft.Mark();
}

void SceneBulletHell::Update() {
	// Check for GameOver
	if (!isGameFail) {
		isGameFail = true;
		for (auto &pPlayer : layerPlayer) {
			if (pPlayer != NULL)
				isGameFail = false;
		}
	}

	// Update text
	if (layerPlayer[playerNumber] != NULL) {
		playerHP.setString("HP: " + std::to_string(int(layerPlayer[playerNumber]->GetHp())) + "/100");
	}
	else {
		playerHP.setString("HP: 0/100");
	}

	//check whether still enemy have not spon
	dt = ft.Mark();
	if (socket.isHost() && !socket.isClient())
		synTimer += dt;
	bool isEnemy = map.Update(dt);

	//check the current number of enemy
	const std::vector<size_t>& brdCount = brd.GetCount();
	size_t nBrdObj = 0;
	for (size_t count : brdCount) {
		nBrdObj += count;
	}

	// check whether the game is success
	int playerAliveNumb = 0;
	for (auto &pPlayer : layerPlayer) {
		if (pPlayer)
			playerAliveNumb++;
	}
	if (!isEnemy && GameObject::getObjectsNumb() == playerAliveNumb && !socket.isClient()) {
		if (socket.isHost()) {
			sf::Packet packet_out;
			packet_out << int(CommResMeth::UDPSocket::PacketType::SIGNAL);
			socket.SendPacket(packet_out);
		}
		isGameSucceed = true;
	}

	//OnlineUpdate : Receive packet add or delete object
	auto & vPackets = socket.GetPacket();
	while (!vPackets.empty()) {
		sf::Packet & packet = vPackets.front();
		int type;
		packet >> type;
		switch(CommResMeth::UDPSocket::PacketType(type)) {
		case CommResMeth::UDPSocket::PacketType::ADD_T:
		{
			float hostTime;
			int objType;
			unsigned int unique_id;
			uint32_t OID;
			sf::Vector2f pos;
			sf::Vector2f vel;
			float rotation;
			float rotSpeed;
			packet >> hostTime >> objType >> OID >> unique_id >> pos.x >> pos.y >> vel.x >> vel.y >> rotation >> rotSpeed;
			assert(packet.endOfPacket());

			std::chrono::duration<float> duration = std::chrono::steady_clock::now() - timeStart;
			float dt = duration.count() - hostTime;
			if (dt < 0)
				dt = 0.0f;

			if (objType == GameObject::ENEMYNOTDEAD) {
				auto pBullet = ObjCreator::CreateEnemyBullet(ObjCreator::EnemyBulletType(OID), pos, vel);
				pBullet->FixedUpdate(dt);
//				layerDefault.insert(pBullet);
			} 
			else if (objType == GameObject::BULLET) {
				auto pBullet = ObjCreator::CreateBullet(ObjCreator::BulletType(OID), pos, rotation);
				pBullet->FixedUpdate(dt);
//				layerDefault.insert(pBullet);
			}
			else {
				assert(1 != 1);
			}
			
			break;
		}
		case CommResMeth::UDPSocket::PacketType::REMOVE:
		{
			assert(socket.isClient());
			uint32_t uni_id;
			packet >> uni_id;
			assert(packet.endOfPacket());
			GameObject::delObject(uni_id);
			break;
		}
		case CommResMeth::UDPSocket::PacketType::CHANGE_T:
		{
			int playerNumber;
			ObjPlayer::StructInput Input;
			float time;
			packet >> time >> playerNumber;
			packet >> Input.isChange >> Input.up >> Input.down >> Input.left >> Input.right >> Input.fire;
			assert(packet.endOfPacket());
			assert(playerNumber >= 0 && playerNumber < totalNumbPlayer);

			std::chrono::duration<float> duration = std::chrono::steady_clock::now() - timeStart;
			float dt = duration.count() - time;
//			if (dt < 0)
//				dt = 0.0f;
			if (layerPlayer[playerNumber]) {
				layerPlayer[playerNumber]->UpdateInput(Input);
				layerPlayer[playerNumber]->FixedUpdateInv(dt);
				layerPlayer[playerNumber]->Update(dt);
				layerPlayer[playerNumber]->FixedUpdate(dt);
			}
			
			// echo the packet if is host
			if (socket.isHost()) {
				sf::Packet packet_echo;
				packet_echo << int(CommResMeth::UDPSocket::PacketType::CHANGE_T) << time << playerNumber;
				packet_echo.append(&Input, sizeof(Input));
				socket.SendPacket(packet_echo);
			}
			break;
		}
		case CommResMeth::UDPSocket::PacketType::SIGNAL:
			assert(socket.isClient());
			isGameSucceed = true;
			break;
		case CommResMeth::UDPSocket::PacketType::CHANGE_POS:
		{
			assert(socket.isClient());
			int totalNumb;
			packet >> totalNumb;
			for (auto &pPlayer : layerPlayer) {
				sf::Vector2f pos;
				packet >> pos.x >> pos.y;
				if (pPlayer) {
					pPlayer->setPosition(pos);
				}
			}
			assert(packet.endOfPacket());
			break;
		}
		case CommResMeth::UDPSocket::PacketType::CHANGE_HP:
		{
			assert(socket.isClient());
			int playerNumb;
			float playerHP;
			packet >> playerNumb >> playerHP;
			assert(packet.endOfPacket());
			if (playerNumb == playerNumber) {
				layerPlayer[playerNumb]->SetHp(playerHP);
			}
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
	if (layerPlayer[playerNumber]) {
		if (socket.isHost() || socket.isClient()) { // Online
			const ObjPlayer::StructInput & input = layerPlayer[playerNumber]->UpdateInput();
			if (input.isChange) {
				sf::Packet packet_out;
				int type = int(CommResMeth::UDPSocket::PacketType::CHANGE_T);
				std::chrono::duration<float> duration = std::chrono::steady_clock::now() - timeStart;
				packet_out << type << duration.count();
				packet_out << playerNumber;
				packet_out.append(&input, sizeof(input));
				socket.SendPacket(packet_out);
			}
		}else if (!socket.isHost() && !socket.isClient()) { // Offline
			layerPlayer[playerNumber]->UpdateInput();
		}
		else {
			assert(1 != 1);
		}
	}

	// Syn player pos
	if (socket.isHost()) {
		if (synTimer > synCooldown) {
			synTimer -= synCooldown;

			sf::Packet packet_out;
			packet_out << int(CommResMeth::UDPSocket::PacketType::CHANGE_POS) << int(totalNumbPlayer);
			for (auto & pPlayer : layerPlayer) {
				if (pPlayer) {
					const sf::Vector2f & pos = pPlayer->getPosition();
					packet_out << pos.x << pos.y;
				}
				else {
					packet_out << 0.0f << 0.0f;
				}
			}
			socket.SendPacket(packet_out);
		}
	}

	// All Obj Update
	if (!socket.isClient()) {
		for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
			(*it)->Update(dt);
		}
	}
	else {
		// Player Update according to input packet
		for (auto &pPlayer : layerPlayer) {
			if (pPlayer) {
				pPlayer->Update(dt);
			}
		}
	}

	//FixedUpdate
	culDt += dt;
	while (culDt >= fixedUpdateDuration) {

		for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
			(*it)->FixedUpdate(fixedUpdateDuration);
		}
		culDt -= fixedUpdateDuration;

		// Disable collison n client
		if (!socket.isClient()) {
			for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
				brd.UpdateObjectPos(*it);
			}
			brd.ProcessCollision();
		}
	}

	// LateUpdate
	for (auto it = layerDefault.begin(); it != layerDefault.end(); it++) {
		(*it)->LateUpdate();
	}

#if defined(_DEBUG_LOG) && defined(_DEBUG)

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
		std::cout << "Deletes:\t" << nDeletes << std::endl;
		std::cout << "Brd:Totoal:\t" << nBrdObj << std::endl;

		nDeletes = 0;
	}
#endif // _DEBUG

	//Remove
	for (auto it = layerDelete.begin(); it != layerDelete.end(); it++) {
		layerDefault.erase(*it);
		brd.RemoveObject(*it);
		if ((*it)->GetType() == GameObject::PLAYER) {
			for (auto & pPlayer : layerPlayer) {
				if (pPlayer == *it) {
					pPlayer = NULL;
				}
			}
		}
		
		if (socket.isHost()) {
			assert(!socket.isClient());
			sf::Packet packet_out;
			uint32_t unique_id = (*it)->GetUniId();
			packet_out << int(CommResMeth::UDPSocket::PacketType::REMOVE) << sf::Uint32(unique_id);
			socket.SendPacket(packet_out);
		}
	}
	GameObject::processDelete();
}

void SceneBulletHell::DrawScene()
{
	//Drawing
	wnd->clear();
	
	wnd->draw(background);
	wnd->draw(playerHP);

#if defined(_DEBUG) && defined(_DEBUG_BOARD)
	brd.Highlight(*wnd);
	brd.View(*wnd);
#endif

	GameObject::draw(*wnd);

	if (isMenuTriger) {
		escMenu.draw(*wnd);
	}
	wnd->display();
}

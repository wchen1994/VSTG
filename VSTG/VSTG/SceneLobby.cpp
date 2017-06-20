#include "SceneLobby.h"

SceneLobby::SceneLobby() : 
	isHostMenu(false), isClientMenu(false), 
	isClientConnecting(false), isClientConnected(false),
	playerCounter(0),
	hostMenu(sf::IntRect(50, 80, 406, 139), "Start Game? No. Player: 1", ObjMenu::MENUFLAG::YES_NO),
	clientMenu(sf::IntRect(50, 80, 550, 400), "Connect to: ", ObjMenu::MENUFLAG::OK_CANCEL)
{
	Button::SettingDefaultButton(butHost, "Host Game", Button::ButtonStyle::MEDIUM);
	butHost.setPosition(sf::Vector2f(300.0f, 150.0f));

	Button::SettingDefaultButton(butJoin, "Join Game", Button::ButtonStyle::MEDIUM);
	butJoin.setPosition(sf::Vector2f(300.0f, 300.0f));

	Button::SettingDefaultButton(butBack, "Back", Button::ButtonStyle::SMALL);
	butBack.setPosition(sf::Vector2f(550.0f, 500.0f));

	boxClientIP.SetPosition(sf::Vector2f(80, 150));
	boxClientIP.SetMaxSize(15);
	boxClientIP.flag = TextBox::flagDIGIT | TextBox::flagSIMBOL;
	boxClientIP.SetPrompt("<IP Address>");

	boxClientPort.SetPosition(sf::Vector2f(80, 200));
	boxClientPort.SetMaxSize(5);
	boxClientPort.flag = TextBox::flagDIGIT;
	boxClientPort.SetPrompt("<Port>");
}

Essential::GameState SceneLobby::Run()
{
	while (Essential::wnd.isOpen()) {
		sf::Event e;
		while (Essential::wnd.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::KeyReleased:
				if (isClientMenu) {
					boxClientIP.Input(e.key);
					boxClientPort.Input(e.key);
				}
				break;
			default:
				Essential::defHandleMsg(e);
			}
		}

		if (isHostMenu) {
			int rc = hostMenu.MenuUpdate();
			Essential::socket.servWait();
			auto & clientInfo = Essential::socket.GetClient();
			if (playerCounter != clientInfo.size()) {
				sf::Packet packet_out;
				playerCounter++;
				assert(playerCounter == clientInfo.size());
				packet_out << int(Essential::PacketType::SIGNAL_SIZE) << playerCounter;
				Essential::socket.SendPacket(packet_out);
				hostMenu.SetTitle("Start Game ? No. Player : " + std::to_string(playerCounter+1));
			}
			if (rc == 1) {
				sf::Packet packet_out;
				packet_out << int(Essential::PacketType::SIGNAL);
				Essential::socket.SendPacket(packet_out);
				isHostMenu = false;
				return Essential::GameState::GAMEHOST;
			}
			else if(rc == 2) {
				Essential::socket.ClearClientInfo();
				playerCounter = 0;
				isHostMenu = false;
			}
		}
		else if (isClientMenu) {
			int rc = clientMenu.MenuUpdate();

			if (!isClientConnected) {
				boxClientIP.Update();
				boxClientPort.Update();
			}

			if (isClientConnecting) {
				std::queue<sf::Packet> & qPackets = Essential::socket.GetPacket();
				while (!qPackets.empty())
				{
					sf::Packet &packet = qPackets.front();
					int type;
					int playerNumber;
					packet >> type;
					if (type == int(Essential::PacketType::SIGNAL_SIZE)) {
						packet >> playerNumber;
						clientMenu.SetTitle("Connected: Player " + std::to_string(playerNumber + 1));
						assert(Essential::playerNumber == 0);
						Essential::playerNumber = playerNumber;
						isClientConnecting = false;
						isClientConnected = true;
					}
					qPackets.pop();
				}
			}
			else if (isClientConnected) {
				std::queue<sf::Packet> & qPackets = Essential::socket.GetPacket();
				while (!qPackets.empty())
				{
					sf::Packet &packet = qPackets.front();
					int type;
					packet >> type;
					qPackets.pop();
					if (type == int(Essential::PacketType::SIGNAL)) {
						isClientConnected = false;
						isClientConnecting = false;
						clientMenu.SetTitle("Connect to : ");
						return Essential::GameState::GAMECLIENT;
					}
				}
				
			}

			if (rc == 1) {
				if (!isClientConnected) {
					unsigned short hostPort = std::stoi(boxClientPort.GetString());
					std::string hostIp = boxClientIP.GetString();
					Essential::socket.Join(hostIp, hostPort, Essential::DEFAULT_CLIENT_PORT);

					clientMenu.SetTitle("Connecting to: " + hostIp);
					sf::Packet packet_out;
					packet_out << int(Essential::PacketType::SIGNAL);
					Essential::socket.SendPacket(packet_out);

					isClientConnecting = true;
				}
			}
			else if (rc == 2) {
				clientMenu.SetTitle("Connect to: ");
				isClientConnecting = false;
				isClientConnected = false;
				isClientMenu = false;
				Essential::playerNumber = 0;
				Essential::socket.FlushPacketQueue();
				//** Future add sendPacke of Signal Exit
			}
		}
		else {
			butHost.Update();
			butJoin.Update();
			butBack.Update();

			if (butHost.getStatus() == Button::ButtonState::Release) {
				Essential::socket.Host(Essential::DEFAULT_HOST_PORT);
				isHostMenu = true;
			}
			if (butJoin.getStatus() == Button::ButtonState::Release) {
				if (boxClientPort.GetString().size() == 0)
					boxClientPort.SetString(std::to_string(Essential::DEFAULT_HOST_PORT));
				isClientMenu = true;
			}
			if (butBack.getStatus() == Button::ButtonState::Release) {
				Essential::socket.Unbind();
				Essential::socket.FlushPacketQueue();
				return Essential::GameState::POP;
			}

		}

		Essential::wnd.clear(sf::Color::Cyan);
		butHost.Draw(Essential::wnd);
		butJoin.Draw(Essential::wnd);
		butBack.Draw(Essential::wnd);
		if (isHostMenu) {
			hostMenu.Draw(Essential::wnd);
		}
		if (isClientMenu) {
			clientMenu.Draw(Essential::wnd);
			boxClientIP.Draw(Essential::wnd);
			boxClientPort.Draw(Essential::wnd);
		}
		Essential::wnd.display();
	}
	return Essential::GameState::POP;
}

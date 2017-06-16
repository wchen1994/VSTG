#include "SceneLobby.h"

SceneLobby::SceneLobby() : 
	isHostMenu(false), isClientMenu(false),
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
			size_t numb = Essential::socket.GetClinetNumb();
			hostMenu.SetTitle("Start Game ? No.Player : " + std::to_string(numb));
			if (rc == 1) {
				return Essential::GameState::GAMEHOST;
			}
			else if(rc == 2) {
				Essential::socket.ClearClientInfo();
				isHostMenu = false;
			}
		}
		if (isClientMenu) {
			int rc = clientMenu.MenuUpdate();
			boxClientIP.Update();
			boxClientPort.Update();
			if (rc == 1) {
				unsigned short hostPort = std::stoi(boxClientPort.GetString());
				Essential::socket.Join(boxClientIP.GetString(), hostPort, Essential::DEFAULT_CLIENT_PORT);
			}
			else if (rc == 2) {
				isClientMenu = false;
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

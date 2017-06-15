#include "SceneLobby.h"

SceneLobby::SceneLobby()
{
	Button::SettingDefaultButton(butHost, "Host Game", Button::ButtonStyle::SMALL);
	butHost.setPosition(sf::Vector2f(300.0f, 250.0f));

	Button::SettingDefaultButton(butJoin, "Join Game", Button::ButtonStyle::SMALL);
	butJoin.setPosition(sf::Vector2f(300.0f, 300.0f));
}

Essential::GameState SceneLobby::Run()
{
	while (Essential::wnd.isOpen()) {
		sf::Event e;
		while (Essential::wnd.pollEvent(e)) {
			switch (e.type)
			{
			default:
				Essential::defHandleMsg(e);
			}
		}

		butHost.Update();
		butJoin.Update();

		butHost.Draw(Essential::wnd);
		butJoin.Draw(Essential::wnd);
	}
	return Essential::GameState::POP;
}

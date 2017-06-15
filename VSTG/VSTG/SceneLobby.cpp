#include "SceneLobby.h"

SceneLobby::SceneLobby()
{
	Button::SettingDefaultButton(butHost, "Host Game", Button::ButtonStyle::MEDIUM);
	butHost.setPosition(sf::Vector2f(300.0f, 150.0f));

	Button::SettingDefaultButton(butJoin, "Join Game", Button::ButtonStyle::MEDIUM);
	butJoin.setPosition(sf::Vector2f(300.0f, 300.0f));

	Button::SettingDefaultButton(butBack, "Back", Button::ButtonStyle::SMALL);
	butBack.setPosition(sf::Vector2f(550.0f, 500.0f));
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
		butBack.Update();

		if (butBack.getStatus() == Button::ButtonState::Release) {
			return Essential::GameState::POP;
		}

		Essential::wnd.clear(sf::Color::Cyan);
		butHost.Draw(Essential::wnd);
		butJoin.Draw(Essential::wnd);
		butBack.Draw(Essential::wnd);
		Essential::wnd.display();
	}
	return Essential::GameState::POP;
}

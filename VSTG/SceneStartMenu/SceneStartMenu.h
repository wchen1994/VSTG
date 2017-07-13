#pragma once

#include "Scene.h"
#include "TextManager.h"
#include "Defines.h"
#include <TGUI\/TGUI.hpp>

#pragma comment(lib, "CommonResourcesMethods")
#pragma comment(lib, "tgui-d")

namespace DllSceneStartMenu {
	class __declspec(dllexport) SceneStartMenu : public CommResMeth::Scene {
	public:
		SceneStartMenu(Scene* const parent = nullptr);
		~SceneStartMenu();
		int Exec() override;
	private:
		sf::Event e;
//		std::shared_ptr<sf::Texture> butTexture;
//		CommResMeth::Button butStart;
//		CommResMeth::Button butOnline;
//		CommResMeth::Button butEdit;
//		CommResMeth::Button butExit;
		tgui::Button::Ptr button;
		tgui::Theme::Ptr theme;
		tgui::Gui gui;
		bool isFocus;
		bool isFullscreen;
		bool isReturn;
		int returnState;
	private: //slot
		void onStartPressed() {
			isReturn = true;
			returnState = GAMESTATE_GAME_OFFLINE;
		}
		void onOnlinePressed() {
			isReturn = true;
			returnState = GAMESTATE_LOBBY;
		}
		void onEditPressed() {
			isReturn = true;
			returnState = GAMESTATE_EDITOR;
		}
		void onExitPressed() {
			isReturn = true;
			returnState = GAMESTATE_POP;
		}
	};

}
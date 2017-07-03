#pragma once

#include "Scene.hpp"
#include "Button.h"

#pragma comment(lib, "CommonResourcesMethods")

namespace DllSceneStartMenu {
	class __declspec(dllexport) SceneStartMenu : public CommResMeth::Scene {
	private:
		sf::Event event;
		std::shared_ptr<sf::Texture> butTexture;
		CommResMeth::Button butStart;
		CommResMeth::Button butOnline;
		CommResMeth::Button butEdit;
		CommResMeth::Button butExit;
		bool isFocus;
	public:
		SceneStartMenu(Scene* const parent = nullptr);
		virtual ~SceneStartMenu() = default;
		CommResMeth::GameState Exec() override;
	};
}
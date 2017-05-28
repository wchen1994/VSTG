#pragma once

#include <set>
#include <chrono>
#include <thread>

#include "Scene.hpp"
#include "Essential.hpp"
#include "GameObject.hpp"
#include "ObjMenu.h"
#include "ObjEnemy.hpp"

struct YCmp {
	bool operator()(const std::shared_ptr<GameObject> lhs, const std::shared_ptr<GameObject> rhs) const {
		if (lhs->getPosition().y * 10000 + lhs->getPosition().x > rhs->getPosition().y * 10000 + rhs->getPosition().x) {
			return true;
		}
		return false;
	}
};

class SceneMapEditor : public Scene {
private:
	class Data {
	private:
		float sponsTime;
		sf::Vector2f initPos;
		char objectID[128];
		size_t hasdID;
		int numPaths;
		sf::Vector2i followPaths[16];
	};
public:
	SceneMapEditor();
	Essential::GameState Run();
	void DrawScene();
	bool MergeFromFile(const std::string filepath);
	bool MergeFromFile();
	bool WriteToFile(const std::string filepath);
	bool WriteToFile();
private:
	bool isExit;
	bool isDrag;
	bool isMouseLeft;
	bool isFocused;
	bool isMenuTriger;
	float timeAtBottom;
	float timeScale;
//	float spriteScale;
	static constexpr float scrollSpeed = 30.0f;
	static constexpr float eraseSize= 20.0f;
//	static constexpr float brushSize = 5.0f;
	std::vector<Data> vdata;
	std::set<std::shared_ptr<GameObject>, YCmp> sortedpObject;
	std::list<std::shared_ptr<GameObject>> lObjectDel;
	std::shared_ptr<sf::Texture> pTexBuffer;
	std::shared_ptr<GameObject> objectBrush;
	sf::CircleShape objectEraser;
	std::shared_ptr<GameObject> dragObject;
	ObjMenu escMenu;
	sf::RectangleShape paintboard;
private:
	void Update();
	void DrawLine(sf::RenderTarget & gfx, const float y);
	float time2dim(const float & dim) const;
	float dim2time(const float & time) const;
	bool inPaintboard(const sf::Vector2f& pos) const;
};
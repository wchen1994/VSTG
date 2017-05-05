#pragma once

#include <fstream>
#include <iostream>
#include <set>

#include "Scene.hpp"
#include "Essential.hpp"
#include "GameObject.hpp"

struct YCmp {
	bool operator()(const sf::Shape *lhs, const sf::Shape *rhs) const {
		if (lhs->getPosition().y > rhs->getPosition().y) {
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
	bool LoadFromFile(const std::string filepath);
	bool WriteToFile(const std::string filepath);
private:
	bool isExit;
	bool isDrag;
	bool isMouseLeft;
	float timeAtBottom;
	float timeScale;
	static constexpr float scrollSpeed = 30.0f;
	static constexpr float eraseSize= 20.0f;
	static constexpr float brushSize = 5.0f;
	std::ifstream infile;
	std::ofstream outfile;
	std::string line;
	std::vector<Data> vdata;
	std::set<sf::CircleShape*, YCmp> sortedpShapes;
	std::list<sf::CircleShape*> lShapeDel;
	sf::CircleShape objectBrush;
	sf::CircleShape objectEraser;
	sf::CircleShape *dragObject;
private:
	void DrawLine(sf::RenderTarget & gfx, const float y);
};
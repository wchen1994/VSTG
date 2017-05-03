#pragma once

#include <fstream>
#include <iostream>
#include <set>

#include "Scene.hpp"
#include "Essential.hpp"
#include "GameObject.hpp"

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
	static constexpr float eraseSize= 20.0f;
	std::ifstream infile;
	std::ofstream outfile;
	std::string line;
	std::vector<Data> vdata;
	std::list<sf::CircleShape*> lShape;
	std::list<sf::CircleShape*> lShapeBuffer;
private:
};
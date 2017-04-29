#pragma once

#include <fstream>
#include <iostream>

#include "Scene.hpp"
#include "Essential.hpp"
#include "GameObject.hpp"

class SceneMapEditor : public Scene {
private:
	class Data {
	private:
		float sponsTime;
		std::shared_ptr<GameObject> pSponsObject;
		std::vector<sf::Vector2i> followPaths;
	};
public:
	SceneMapEditor();
	Essential::GameState Run();
	bool LoadFromFile(const std::string filepath);
	bool WriteToFile(const std::string filepath);
private:
	bool isExit;
	std::ifstream infile;
	std::ofstream outfile;
	std::string line;
	std::vector<Data> vdata;
};
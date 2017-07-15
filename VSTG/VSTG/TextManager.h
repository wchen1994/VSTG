#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <SFML/System.hpp>

#define MAX_TEXT_NUM 2048

class TextManager {
public:
	TextManager(const std::string& filepath);
	sf::String getText(uint32_t id) { return texts[id % MAX_TEXT_NUM]; }
private:
	std::wifstream csvfile;
	sf::String texts[MAX_TEXT_NUM];
};

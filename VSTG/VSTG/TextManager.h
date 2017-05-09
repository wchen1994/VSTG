#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#define MAX_TEXT_NUM 2048

class TextManager {
public:
	TextManager(const std::string& filepath);
	std::string getText(uint32_t id) { return texts[id % MAX_TEXT_NUM]; }
private:
	std::ifstream csvfile;
	std::string texts[MAX_TEXT_NUM];
};

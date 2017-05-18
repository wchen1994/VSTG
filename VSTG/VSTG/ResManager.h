#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <memory>

class ResManager {
public:
	std::shared_ptr<sf::Texture> SetRes(std::string path);
	std::shared_ptr<sf::Texture> GetRes(std::string path);
	bool killLonePtr();
private:
	std::map<std::string, std::shared_ptr<sf::Texture>> texmap;
};
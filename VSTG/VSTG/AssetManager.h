#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <memory>

class AssetManager {
public:
	AssetManager();
	std::shared_ptr<sf::Texture> GetTexture(std::string const& path);
	bool killLonePtr();
private:
	std::map<std::string, std::shared_ptr<sf::Texture>> m_pTexMap;
};
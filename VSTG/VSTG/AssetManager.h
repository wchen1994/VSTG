#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <assert.h>
#include <memory>

class AssetManager {
public:
	static AssetManager assetManager;
public:
	AssetManager();
	std::shared_ptr<sf::Texture> GetTexture(std::string const& path);
	std::shared_ptr<sf::SoundBuffer> GetSoundBuffer(std::string const& path);
	bool killLonePtr();
private:
	std::map<std::string, std::shared_ptr<sf::Texture>> m_pTexMap;
	std::map<std::string, std::shared_ptr<sf::SoundBuffer>> m_pSoundMap;
};

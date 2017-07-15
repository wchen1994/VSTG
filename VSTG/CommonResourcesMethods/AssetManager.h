#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <assert.h>
#include <memory>
#include <fstream>
#include "Defines.h"

namespace CommResMeth {
	class __VSTG_API AssetManager {
	public:
		static AssetManager m_instance;
	private:
		AssetManager();
	public:
		static std::shared_ptr<sf::Texture> GetTexture(std::string const& path);
		static std::shared_ptr<sf::SoundBuffer> GetSoundBuffer(std::string const& path);
		static std::shared_ptr<std::vector<char>> GetBlock(std::string const& path, size_t max_size);
		static std::shared_ptr<sf::Font> GetFont(std::string const& path);
		bool killLonePtr();
	private:
		std::map<std::string, std::shared_ptr<sf::Texture>> m_pTexMap;
		std::map<std::string, std::shared_ptr<sf::SoundBuffer>> m_pSoundMap;
		std::map<std::string, std::shared_ptr<std::vector<char>>> m_pBlock;
		std::map<std::string, std::shared_ptr<sf::Font>> m_pFont;
	};
}
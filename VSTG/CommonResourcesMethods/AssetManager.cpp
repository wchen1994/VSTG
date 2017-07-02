#include "AssetManager.h"

namespace CommResMeth {

	AssetManager AssetManager::assetManager;

	AssetManager::AssetManager()
	{
	}

	std::shared_ptr<sf::Texture> AssetManager::GetTexture(std::string const& path)
	{
		auto pTexFound = m_pTexMap.find(path);
		if (pTexFound != m_pTexMap.end()) {
			return pTexFound->second;
		}
		else {
			auto& pTex = m_pTexMap[path] = std::make_shared<sf::Texture>(sf::Texture());
			pTex->loadFromFile(path);
			return pTex;
		}
	}

	std::shared_ptr<sf::SoundBuffer> AssetManager::GetSoundBuffer(std::string const & path)
	{
		auto itSound = m_pSoundMap.find(path);
		if (itSound == m_pSoundMap.end()) {
			auto soundBuffer = std::make_shared<sf::SoundBuffer>(sf::SoundBuffer());
			soundBuffer->loadFromFile(path);
			m_pSoundMap[path] = soundBuffer;
			return soundBuffer;
		}
		else {
			return itSound->second;
		}
		return nullptr;
	}

	std::shared_ptr<std::vector<char>> AssetManager::GetBlock(std::string const & path, size_t max_size)
	{
		auto itBlock = m_pBlock.find(path);
		if (itBlock == m_pBlock.end()) {
			std::ifstream in_file;
			in_file.open(path, std::ios::binary | std::ios::in);
			in_file.seekg(0, in_file.end);
			size_t size = in_file.tellg();
			if (size != max_size)
				return nullptr;
			in_file.seekg(0, in_file.beg);
			std::shared_ptr<std::vector<char>> pBlock = std::make_shared<std::vector<char>>(std::vector<char>(size));
			in_file.read(pBlock->data(), size);
			m_pBlock[path] = pBlock;
			return pBlock;
		}
		else {
			return itBlock->second;
		}
		return nullptr;
	}

	bool AssetManager::killLonePtr()
	{
		for (auto it = m_pTexMap.begin(); it != m_pTexMap.end();) {
			if (it->second.use_count() == 1) {
				m_pTexMap.erase(it++);
			}
			else {
				it++;
			}
		}
		return false;
	}

}
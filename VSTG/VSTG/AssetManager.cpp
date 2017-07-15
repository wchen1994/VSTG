#include "AssetManager.h"

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



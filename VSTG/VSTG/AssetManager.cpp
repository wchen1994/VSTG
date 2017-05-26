#include "AssetManager.h"

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



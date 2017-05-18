#include "ResManager.h"

std::shared_ptr<sf::Texture> ResManager::SetRes(std::string path)
{
	std::shared_ptr<sf::Texture> pTex = std::make_shared<sf::Texture>(sf::Texture());
	pTex->loadFromFile(path);
	auto pair = texmap.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>(path, pTex));
	assert(pair.second);
	return pair.first->second;
}

std::shared_ptr<sf::Texture> ResManager::GetRes(std::string path)
{
	// TODO: insert return statement here
	std::map<std::string, std::shared_ptr<sf::Texture>>::iterator it = texmap.find(path);
	if (it == texmap.end()) {
		return SetRes(path);
	}
	return it->second;
}

bool ResManager::killLonePtr()
{
	for (auto it = texmap.begin(); it != texmap.end();/*no increment*/) {
		if (it->second.use_count() == 1) {
			texmap.erase(it++);
		}
		else {
			it++;
		}
	}
	return false;
}


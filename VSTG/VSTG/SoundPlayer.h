#pragma once

#include <memory>
#include <SFML/Audio.hpp>

#include "AssetManager.h"

#define MAX_SOUND_NUMB 10

class SoundPlayer {
public:
	struct StructSound {
		float sqDist;
		float duration;
		size_t hashName;
		sf::Sound sound;
		std::shared_ptr<sf::SoundBuffer> pBuffer;
	};
	struct DistCmp {
		// Less compare
		bool operator()(const StructSound* first, const StructSound* second) {
			if (first->sqDist <= second->sqDist) {
				if (first->sound.getPlayingOffset() <= second->sound.getPlayingOffset()) {
					if (first->hashName > second->hashName) {
						return true;
					}
				}
			}
			return false;
		}
	};
public:
	SoundPlayer();
	void play(std::string const & path, sf::Vector2f pos);
private:
	std::set<StructSound*, DistCmp> setSound;
};
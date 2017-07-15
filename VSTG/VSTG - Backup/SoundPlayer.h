#pragma once

#include <memory>
#include <chrono>
#include <SFML/Audio.hpp>

#include "AssetManager.h"
#include "Essential.hpp"

#define MAX_SOUND_NUMB 20

class SoundPlayer {
public:
	static SoundPlayer soundPlayer;
public:
	struct StructSound {
		float sqDist;
		float duration;
		float spornTime;
		uintptr_t id;
		sf::Sound sound;
		std::shared_ptr<sf::SoundBuffer> pBuffer;
	};
	struct DistCmp {
		// Less compare
		bool operator()(const StructSound* first, const StructSound* second) {
			if (first->sqDist < second->sqDist) {
				return true;
			}
			else if (first->sqDist == second->sqDist) {
				if (first->spornTime > second->spornTime) {
					return true;
				}
				else if (first->spornTime == second->spornTime) {
					if (first->id < second->id) {
						return true;
					}
				}
			}

			return false;
		}
	};
public:
	SoundPlayer();
	void play(std::string const & path, const sf::Vector2f & pos, const float duration=0.5f);
private:
	std::set<StructSound*, DistCmp> setSound;
};
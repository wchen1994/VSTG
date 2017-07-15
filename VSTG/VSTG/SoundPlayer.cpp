#include "SoundPlayer.h"

#include <iostream>

SoundPlayer SoundPlayer::soundPlayer;

SoundPlayer::SoundPlayer()
{
}

void SoundPlayer::play(std::string const & path, const sf::Vector2f & pos, const float duration)
{
	const auto & pSoundBuffer = AssetManager::assetManager.GetSoundBuffer(path);
	StructSound *structSound = new StructSound();
	structSound->id = reinterpret_cast<std::uintptr_t>(pSoundBuffer.get());
	structSound->sound.setBuffer(*pSoundBuffer);
	structSound->sqDist = pos.x*pos.x + pos.y*pos.y;
	structSound->duration = duration;
	structSound->pBuffer = pSoundBuffer;
	std::chrono::duration<float> time = std::chrono::steady_clock::now() - Essential::timeStart;
	structSound->spornTime = time.count();
	if (structSound->duration > 0) {
		structSound->sound.setLoop(false);
	}
	else {
		structSound->sound.setLoop(true);
	}

	for (auto itSound = setSound.begin(); itSound != setSound.end();) {
		float offset = (*itSound)->sound.getPlayingOffset().asSeconds();
		if ((*itSound)->sound.getStatus() == sf::Sound::Status::Stopped || 
			(*itSound)->sound.getPlayingOffset().asSeconds() > (*itSound)->duration) {
			delete *itSound;
			itSound = setSound.erase(itSound);
		}
		else {
			itSound++;
		}
	}

	std::cout << setSound.size() << std::endl;

	const auto &pair = setSound.insert(structSound);

	structSound->sound.play();

	if (!pair.second) {
		delete structSound;
		return;
	}

	if (setSound.size() >= MAX_SOUND_NUMB) {
		auto itSound = --setSound.end();
		(*itSound)->sound.stop();
		delete *itSound;
		setSound.erase(itSound);
	}
}

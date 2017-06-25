#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
}

void SoundPlayer::play(std::string const & path, sf::Vector2f pos)
{
	auto & pSoundBuffer = AssetManager::assetManager.GetSoundBuffer(path);
	StructSound *structSound = new StructSound();
	structSound->sound.setBuffer(*pSoundBuffer);
	structSound->sqDist = pos.x*pos.x + pos.y*pos.y;
	structSound->duration = pSoundBuffer->getDuration().asSeconds();
	structSound->pBuffer = pSoundBuffer;
	if (structSound->duration > 0) {
		structSound->sound.setLoop(false);
	}
	else {
		structSound->sound.setLoop(true);
	}
	structSound->sound.play();

	setSound.insert(structSound);
	for (auto &itSound = setSound.begin(); itSound != setSound.end(); itSound++) {
		if ((*itSound)->sound.getPlayingOffset().asSeconds() > (*itSound)->duration) {
			(*itSound)->sound.stop();
			delete *itSound;
			setSound.erase(itSound);
		}
	}
	if (setSound.size() > MAX_SOUND_NUMB) {
		auto itSound = --setSound.end();
		(*itSound)->sound.stop();
		delete *itSound;
		setSound.erase(itSound);
	}
}

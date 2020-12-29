#pragma once

#include "common.h"

class SoundPack
{
private:
	sf::SoundBuffer playerDamagedSoundBuffer;
	sf::SoundBuffer shootSoundBuffer;
	sf::SoundBuffer outOfAmmoSoundBuffer;
	sf::SoundBuffer hitRockSoundBuffer;
	sf::SoundBuffer gameOverSoundBuffer;
	sf::SoundBuffer lifeUpSoundBuffer;
	sf::SoundBuffer clickSoundBuffer;

public:
	sf::Sound playerDamagedSound;
	sf::Sound shootSound;
	sf::Sound outOfAmmoSound;
	sf::Sound hitRockSound;
	sf::Sound gameOverSound;
	sf::Sound lifeUpSound;
	sf::Sound clickSound;

	float volume;

	SoundPack();
	~SoundPack() {};
};


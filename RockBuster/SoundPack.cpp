#include "SoundPack.h"

SoundPack::SoundPack()
{
	if (!this->playerDamagedSoundBuffer.loadFromFile("Sounds/take_demage.wav"))
	{
		std::cout << "ERROR: SoundPack::SoundPack(): player demaged sound cannot be loaded\n";
	}

	this->playerDamagedSound.setBuffer(this->playerDamagedSoundBuffer);


	if (!this->shootSoundBuffer.loadFromFile("Sounds/shoot.wav"))
	{
		std::cout << "ERROR: SoundPack::SoundPack(): shoot sound cannot be loaded\n";
	}

	this->shootSound.setBuffer(this->shootSoundBuffer);

	if (!this->outOfAmmoSoundBuffer.loadFromFile("Sounds/out_of_ammo.wav"))
	{
		std::cout << "ERROR: SoundPack::SoundPack(): out of ammo sound cannot be loaded\n";
	}

	this->outOfAmmoSound.setBuffer(this->outOfAmmoSoundBuffer);


	if (!this->hitRockSoundBuffer.loadFromFile("Sounds/hit_rock.wav"))
	{
		std::cout << "ERROR: SoundPack::SoundPack(): hit rock sound cannot be loaded\n";
	}

	this->hitRockSound.setBuffer(this->hitRockSoundBuffer);


	if (!this->gameOverSoundBuffer.loadFromFile("Sounds/game_over.wav"))
	{
		std::cout << "ERROR: SoundPack::SoundPack(): game over sound cannot be loaded\n";
	}

	this->gameOverSound.setBuffer(this->gameOverSoundBuffer);

	if (!this->lifeUpSoundBuffer.loadFromFile("Sounds/life_up.wav"))
	{
		std::cout << "ERROR: SoundPack::SoundPack(): life up sound cannot be loaded\n";
	}

	this->lifeUpSound.setBuffer(this->lifeUpSoundBuffer);

	if (!this->clickSoundBuffer.loadFromFile("Sounds/click.wav"))
	{
		std::cout << "ERROR: SoundPack::SoundPack(): click sound cannot be loaded\n";
	}

	this->clickSound.setBuffer(this->clickSoundBuffer);

	this->volume = 100.f;
}

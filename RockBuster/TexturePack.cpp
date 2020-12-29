#include "TexturePack.h"

TexturePack::TexturePack()
{

	// Spaceship

	if (!this->normalPlayerTexture.loadFromFile("Textures/spaceship.png"))
	{
		std::cout << "ERROR: TexturePack::TexturePack(): player normal texture cannot be loaded\n";
	}

	if (!this->brokenPlayerTexture.loadFromFile("Textures/spaceship_broken.png"))
	{
		std::cout << "ERROR: TexturePack::TexturePack(): player broken texture cannot be loaded\n";
	}

	// Background

	if (!this->backgroundTexture.loadFromFile("Textures/background.jpg"))
	{
		std::cout << "ERROR: TexturePack::TexturePack(): background texture cannot be loaded\n";
	}

	// Rocks and stuff

	if (!this->fireTexture.loadFromFile("Textures/fire.png"))
	{
		std::cout << "ERROR: TexturePack::TexturePack(): fire texture cannot be loaded\n";
	}

	for (int i = 0; i < 10; i++)
	{
		if (!this->rockTextures[i].loadFromFile("Textures/rock" + std::to_string(i) + ".png"))
		{
			std::cout << "ERROR: TexturePack::TexturePack(): rock texture cannot be loaded\n";
		}
	}

	// Other

	if (!this->bulletTexture.loadFromFile("Textures/bullet.png"))
	{
		std::cout << "ERROR: TexturePack::TexturePack(): bullet texture cannot be loaded\n";
	}

	if (!this->bonusTexture.loadFromFile("Textures/tools.png"))
	{
		std::cout << "ERROR: TexturePack::TexturePack(): bonus texture cannot be loaded\n";
	}

	if (!this->explosionTexture.loadFromFile("Textures/explosion1.png"))
	{
		std::cout << "ERROR: TexturePack::TexturePack(): explosion texture cannot be loaded\n";
	}
}
